import sys
sys.tracebacklimit = 0
import re

class MiniLisp:
    def __init__(self):
        pass

    def interpret(self, file):
        if file:
            with open(file, "r") as f:
                lines = f.read().split("\n")
            f.close()
        else:
            lines = []
            while True:
                try:
                    line = input()
                except EOFError:
                    break
                else:
                    lines.append(line)

        text = f'({"".join(lines)})'
        tokens = text.replace("(", " ( ").replace(")", " ) ").split()
        forest = self.dfs(tokens)
        if len(tokens) != 0:
            raise SyntaxError("unexpected Syntax")
        env = Env()
        for tree in forest:
            if len(tree) == 1:
                raise SyntaxError("undefined Operation")
            cal(tree, env)

    def dfs(self, tokens):
        if len(tokens) == 0:
            raise SyntaxError("unexpected EOF")
        token = tokens.pop(0)
        if token == "(":
            L = []
            while tokens[0] != ")":
                L.append(self.dfs(tokens))
            tokens.pop(0)
            return L
        else:
            try:
                return int(token)
            except:
                return token


def cal(exp, env):
    if isinstance(exp, str):
        return env.locate(exp)[exp]
    if isinstance(exp, int):
        return exp

    op, *args = exp

    if op == "define":
        reg = re.compile(r"^([a-z]|[0-9]|-)*$")
        if not reg.match(args[0]):
            raise SyntaxError("Invalid variable name")
        env[args[0]] = cal(args[1], env)
        return

    if op == "fun":
        name, *body = args
        return function(name, body, env)

    if op == "if":
        texp, yexp, nexp = args
        tmp = cal(texp, env)
        if not isinstance(tmp, bool):
            raise TypeError("if test-exp didn't return bool")
        if cal(texp, env):
            return cal(yexp, env)
        else:
            return cal(nexp, env)

    return cal(op, env)(*[cal(arg, env) for arg in args])


import operator as op
from functools import reduce


class Env(dict):
    def __init__(self, params={}, args={}, outer=None):
        self.outer = outer
        super().__init__(self)
        std_env = {
            "#t": True,
            "#f": False,
            "+": add,
            "-": sub,
            "*": mul,
            "/": div,
            "mod": mod,
            "=": equal,
            ">": greaterthan,
            "<": lessthan,
            "and": andOperator,
            "or": orOperator,
            "not": notOperator,
            "print-num": print_num,
            "print-bool": print_bool,
        }
        self.update(std_env)
        self.update(zip(params, args))

    def locate(self, var):
        if var in self:
            return self
        elif self.outer:
            return self.outer.locate(var)
        else:
            raise Exception(f"Variable not found: {var}")


def add(*args):
    if len(args) < 2:
        raise TypeError("add requires at least 2 arguments")
    check_int_type(args)
    return reduce(op.add, args)


def sub(*args):
    if len(args) != 2:
        raise TypeError("sub requires exactly 2 arguments")
    check_int_type(args)
    return op.sub(*args)


def mul(*args):
    if len(args) < 2:
        raise TypeError("mul requires at least 2 arguments")
    check_int_type(args)
    return reduce(op.mul, args)


def div(*args):
    if len(args) != 2:
        raise TypeError("div requires exactly 2 arguments")
    check_int_type(args)
    return op.floordiv(*args)


def mod(*args):
    if len(args) != 2:
        raise TypeError("mod requires exactly 2 arguments")
    check_int_type(args)
    return op.mod(*args)


def equal(*args):
    if len(args) < 2:
        raise TypeError("equal requires at least 2 arguments")
    check_int_type(args)
    return all(args[0] == arg for arg in args)


def lessthan(*args):
    if len(args) != 2:
        raise TypeError("lessthan requires exactly 2 arguments")
    check_int_type(args)
    return op.lt(*args)


def greaterthan(*args):
    if len(args) != 2:
        raise TypeError("greaterthan requires exactly 2 arguments")
    check_int_type(args)
    return op.gt(*args)


def andOperator(*args):
    if len(args) < 2:
        raise TypeError("and requires at least 2 arguments")
    check_bool_type(args)
    return reduce(op.and_, args)


def orOperator(*args):
    if len(args) < 2:
        raise TypeError("or requires at least 2 arguments")
    check_bool_type(args)
    return reduce(op.or_, args)


def notOperator(*args):
    if len(args) != 1:
        raise TypeError("not requires exactly 1 argument")
    check_bool_type(args)
    return op.not_(*args)


def check_int_type(args):
    for i in args:
        if type(i) is not int:
            raise TypeError(f"Expect 'number' but got {i}")


def check_bool_type(args):
    for i in args:
        if type(i) is not bool:
            raise TypeError(f"Expect 'boolean' but got {i}")

def print_num(*args):
    if len(args) != 1:
        raise SyntaxError("Print-num requires exactly 1 argument")
    if isinstance(args[0], int):
        print(args[0])
    else:
        raise TypeError(f"Print-num can only print number but got {args[0]}")

def print_bool(*args):
    if len(args) != 1:
        raise SyntaxError("Print-bool requires exactly 1 argument")
    if isinstance(args[0], bool):
        print(args[0])
    else:
        raise TypeError(f"Print-bool can only print bool but got {args[0]}")

class function:
    def __init__(self, params, body, env):
        self.params = params
        self.body = body
        self.env = env

    def __call__(self, *args):
        if(len(self.params) != len(args)):
            raise TypeError("Invalid number of arguments")
        
        nenv = Env(self.params, args, self.env)

        res = None
        for exp in self.body:
            res = cal(exp, nenv)

        return res


import argparse

if __name__ == "__main__":
    ml = MiniLisp()
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", type=str, help="Input file")
    args = parser.parse_args()

    ml.interpret(args.f)

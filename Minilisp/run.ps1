Get-ChildItem -Path .\data2 | ForEach-Object {
    Write-Host("python test.py -f data2/$_")
    python main.py -f data2/$_
}

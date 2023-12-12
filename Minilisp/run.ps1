Get-ChildItem -Path .\data | ForEach-Object {
    Write-Host("python test.py -f data/$_")
    python main.py -f data/$_
}

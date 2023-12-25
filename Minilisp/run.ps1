Get-ChildItem -Path .\pdata | ForEach-Object {
    Write-Host("python test.py -f pdata/$_")
    python main.py -f pdata/$_
}

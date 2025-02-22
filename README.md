## clion  
## wsl  
## docker  
## drogon  
## odb  
## odbc  
## postman  
## vscode  
## navicat  
## hex reader  

``` javascript
[MSSQL]
Description = MS SQL Server  
Driver = ODBC Driver 18 for SQL Server  
Server = 192.168.41.234  
Database = test  
Port = 1433  
User = sa  
Password = mypass  
TrustServerCertificate = Yes  

sqlcmd -S 192.168.41.234 -U sa -C  
SELECT name FROM sys.databases;  
GO  
isql -v MSSQL sa mypass  
powershell  
New-NetFirewallRule -DisplayName "Allow SQL Server" -Direction Inbound -Action Allow -Protocol TCP -LocalPort 1433  
```  

# X11 in WSL2

In powershell:
```
(ipconfig | Select-String -Pattern 'WSL' -Context 1, 5).Context.PostContext | Select-String -Pattern 'IPv4'
```

In WSL:
```
sudo service ssh start
export DISPLAY=<IP_ADDRESS_FROM STEP_1>:0.0
```

Open XLaunch with default settings  (no access control)

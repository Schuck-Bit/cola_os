copy Objects\ExecutableFile.hex ExecutableFile.hex
del /Q Listings\*.*
del /Q Objects\*.*
del /Q *.txt
del /Q *.ini
del /Q *.bak
del /Q *.plg
del /Q *.dep
del /Q *.Administrator
rmdir /s/q DebugConfig
exit
SET PATH=C:\Keil C\ARM\ARMCLANG\Bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\MATLAB\R2016a\runtime\win64;C:\Program Files\MATLAB\R2016a\bin;C:\Program Files\MATLAB\R2016a\polyspace\bin;C:\Program Files\Cloudflare\Cloudflare WARP\;C:\Program Files\Docker\Docker\resources\bin;C:\Program Files\Git\cmd;C:\Users\Pham Son\AppData\Local\Microsoft\WindowsApps;;C:\intelFPGA_lite\17.0\modelsim_ase\win32aloem;C:\Microsoft VS Code\bin
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"C:\Keil C\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\app_i2c.__i"
"C:\Keil C\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\app_uart.__i"
"C:\Keil C\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\bh1750.__i"
"C:\Keil C\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\main.__i"
"C:\Keil C\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\misc.__i"
"C:\Keil C\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\stm32f10x_i2c.__i"
"C:\Keil C\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\stm32f10x_rcc.__i"
"C:\Keil C\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\stm32f10x_usart.__i"
"C:\Keil C\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\startup_stm32f10x_md._ac"
"C:\Keil C\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\system_stm32f10x.__i"
"C:\Keil C\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\stm32f10x_exti.__i"
"C:\Keil C\ARM\ARMCLANG\Bin\ArmLink" --Via ".\Objects\CamBienBH1750.lnp"

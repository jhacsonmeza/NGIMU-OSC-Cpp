# NGIMU-OSC-Cpp

C++ code example to receive data from [NGIMU](http://x-io.co.uk/ngimu/) over Wi-Fi through OSC messages using [oscpack](http://www.rossbencina.com/code/oscpack) library which was recompiled in Visual Studio 2017 (vc15) from [this respository](https://github.com/yoggy/liboscpack_1_1_0-vc12).

There are two code examples: NGIMU.cpp receive OSC messages in an independent and infinite thread and show them until ctrl-c is pressed. NGIMU_MainLoop.cpp receive OSC messages in your own main loop. This allows you to manipulate acquired data, for example, in NGIMU_MainLoop.cpp code in the main function received data in 100 for-loop iterations is stored into NGIMUdata.txt file. This acquired data is stored in global variables in order to get a message in the OSC thread and then use it in the main loop thread.

Principal OSC message received in these code examples are /quaternion and /sensors. To know more about these messages and obtain additional information, see the [NGIMU User Manual](http://x-io.co.uk/downloads/NGIMU-User-Manual-v1.3.pdf).
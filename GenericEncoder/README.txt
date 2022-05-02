1.GenericEncoder:
===============
A wrapper for Lame encoder to convert wav to mp3 files.
It is a multithreaded application which utilizes cpu cores
by spawning threads equal to cpu cores and assign each thread 
an encoder task(convert a wav file to mp3 file).

Programming language used = c++11

Development platform = Cygwin.

Tested on = Cygwin

2.Design
=========
A Link to class diagram is provided in "./GenericEncoder/docs/design.txt" file

3.Code Structure
================
$ ls -lstr

 Reader  =====>Reads filenames from the folder given as input
 Logger  =====>For tracing purpose
 Encoder =====>This does the actual encoding
 Common  ======>Common header files and main.cpp
 Framework ====>Frameworks required for our app  threadpool, task, threadMessageQueue
     Types===========> data types used by application
     ThreadPool======> create thread and schedule tasks.
     MessageQueue====> Generic message queue which can be used by threads for communication.
     Task        ====> Generic task. Users can implement this interace for this use.(i.e. Encoder task implemented this)

 Platform====>Lower level soure code and libraries(ex: lame libraries)
 Docs========>Design document of Generic Encoder is placed here
 TestData====>wav files for testing
 obj=========>Folder generated dynamically upon builing
 make========>make file for windows and linux
 bin=========>executables
 README.txt==>Starting point for Generic encoder


4.Build steps:
============

 Linux/Cygwin:
 ======
 Makefile is provided inside "./GenericEncoder/make/" folder. Navigate to this folder and run below command.
 
   make
  
 Thats it. Now you have the binary file generated under folder "./GenericEncoder/bin/"

 To clean
   make clean

 Windows:(Note: The below steps are not verified due to windows build environment not available)
 ========
 Makefile.win is provided inside "./GenericEncoder/make/" folder. Navigate to this folder and run below command.
 
   nmake
  
 Thats it. Now you have the binary file generated under folder "./GenericEncoder/bin/"

 To clean
   nmake clean


5.USAGE:
========
Navigate to the binary folder "./GenericEncoder/bin/" and invoke the binary with foldername as argument

$ ./WavToMp3Encoder.exe ../TestData/

sample output:
==============
INFO:MAIN:Found 5 files for encoding
INFO:WAVTOMP3ENCODER:Encoding in progress(0/5)
INFO:WAVTOMP3ENCODER:Encoding in progress(5/5)
INFO:WAVTOMP3ENCODER:Encoding of All Files Completed, Check the input folder for Encoded Files.
 
 Note: Few Test data tracks(wav) are placed under the folder "./GenericEncoder/TestData/". You can make use 
        of it for your basic testing
Interactive Video Streaming is an open source sample project provided by BytePlus RTC. This topic describes how to run this sample project to try an interactive video streaming.

## **Note**

After using the project file to build an application, you can use the built application to have an interactive video streaming.
You and your colleagues must join the same room to have an interactive video streaming.
This open-source project doesn't support Effects-related function. Please download [BytePlus RTC APP](https://docs.byteplus.com/byteplus-rtc/docs/75707#download-solution-demo) to experience it.
If you have installed the BytePlus RTC APP, please uninstall it before compiling and running the sample project. Otherwise, an installation failure message will be displayed.

## **Prerequisites**

- Android Studio ([Chipmunk](https://developer.android.com/studio/releases) version recommended)
	

- [Gradle](https://gradle.org/releases/) (version: gradle-7.4.2-all)
	

- Real device that is running Android 4.4 or later
	

- [BytePlus developer account](https://console.byteplus.com/auth/login/)
	

### **Project setup**

### **Step 1: Obtain AppID and AppKey**

Obtain the AppID and AppKey by creating an application on the [App Management](https://console.byteplus.com/rtc/listRTC) page or using the created application in the BytePlus RTC console.

### **Step 2: Obtain the Access Key ID and Secret Access Key**

Obtain the **AccessKeyID and SecretAccessKey** on the [Key Management](https://console.byteplus.com/iam/keymanage) page in the BytePlus RTC console.

### **Step 3: Build project**

1. Launch Android Studio and open the folder `RTC_InteractiveVideoStream_Demo/Android/RTCSolution`.
	

2. Enter the **HeadUrl**.<br>
	Open the file `component/ToolKit/gradle.properties` and enter the **HeadUrl**.<br>
    You can use **https://demo.byteplus.com/rtc/demo/rtc_demo_special/** as the test domain name of the server. However, this domain name only provides testing running and cannot be used for official operations.
    <img src="https://lf3-static.bytednsdoc.com/obj/eden-cn/pkupenuhr/androidlogin.png" width="500px" >

3. **Enter AppID, AppKey, AccessKeyID, and SecretAccessKey.** 
	Open the file`component/JoinRTSParamsKit/gradle.properties`in the root directory and enter the **AppID, AppKey, AccessKeyID, and SecretAccessKey.** <br>
    <img src="https://lf3-static.bytednsdoc.com/obj/eden-cn/pkupenuhr/androidappid.png" width="500px" >

### **Step 4: Compile and run**

1. Connect your mobile phone to the computer, and enable the debugging feature in the Developer option on your phone. Once the device is successfully connected, the device name will be displayed in the upper right corner of the page.
<img src="https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_cdaddefa6288c02647ed31cc7f9b704a.png" width="500px" >


2. Select **Run** > **Run 'app’** to compile the sample project. A new app will be added to your Android device after the sample project is compiled. Some mobile phones may require you to confirm the installation twice. Please select “Confirm Installation”.<br>
<img src="https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_a1d79391662abafc5ff5965453a49070.png" width="500px" >

The following figure shows the screen when the app starts running.<br>
<img src="https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_8dba08769cb16c0a93724fa34a23c452.jpg" width="200px" >

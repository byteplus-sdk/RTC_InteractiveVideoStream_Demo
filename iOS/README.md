Interactive video streaming is an open source sample project provided by BytePlus RTC. This topic describes how to run this sample project to try the RTC Interactive video streaming.

## **Note**

After using the project file to build an application, you can use the built application for interactive video streaming.
You and your colleagues must join the same room to have an interactive video streaming.
This open-source project doesn't support Effects-related function. Please download [BytePlus RTC APP](https://docs.byteplus.com/byteplus-rtc/docs/75707#download-solution-demo) to experience it.

## **Prerequisites**

- [Xcode](https://developer.apple.com/download/all/?q=Xcode) 14.0+
	

- Real device that is running iOS 12.0 or later
	

- [AppleID](http://appleid.apple.com/)
	

- [BytePlus developer account](https://console.byteplus.com/auth/login/)
	

- [CocoaPods](https://guides.cocoapods.org/using/getting-started.html#getting-started) 1.10.0+
	

## **Project setup**

### **Step 1: Obtain AppID and AppKey**

Obtain the AppID and AppKey by creating an application on the [App Management](https://console.byteplus.com/rtc/listRTC) page or using the created application in the BytePlus RTC console.

### **Step 2: Obtain AccessKey** **ID** **and SecretAccessKey**

Obtain the **AccessKeyID and SecretAccessKey** on the [Key Management](https://console.byteplus.com/iam/keymanage) page in the BytePlus RTC console.

### **Step 3: Build project**

1. Open a CLI on a terminal and go to the root directory ` RTC_InteractiveVideoStream_Demo/iOS/RTCSolution`.
    <img src="https://lf3-static.bytednsdoc.com/obj/eden-cn/pkupenuhr/cd.jpg" width="500px" >

2. Run the `pod install` command to build the project.<br>
    <img src="https://lf3-static.bytednsdoc.com/obj/eden-cn/pkupenuhr/podinstall.jpg" width="500px" >


3. Go to the root directory `RTC_InteractiveVideoStream_Demo/iOS/RTCSolution`. Launch Xcode and open the file `RTCSolution.xcworkspace<br>
    <img src="https://lf3-static.bytednsdoc.com/obj/eden-cn/pkupenuhr/6f6e9cda-a1e8-4d4e-97bf-a7df712810f8.png" width="500px" >

4. In Xcode, open the file `Pods/Development Pods/ToolKit/BuildConfig.h` .
	

5. Enter **HeadUrl**.<br>
 You can use **https://demo.byteplus.com/rtc/demo/rtc_demo_special/login** as the test domain name of the server. However, this domain name only provides testing running and cannot be used for official operations.
    <img src="https://lf3-static.bytednsdoc.com/obj/eden-cn/pkupenuhr/4e5ec753-892c-4bbe-9197-fe14cc914890.png" width="500px" >

6. **Enter AppID, AppKey, AccessKeyID, and SecretAccessKey.** <br>
Enter the **AppID, AppKey, AccessKeyID**, and **SecretAccessKey** obtained from the BytePlus RTC console in the corresponding fields of the file `BuildConfig.h`.<br>
    <img src="https://lf3-static.bytednsdoc.com/obj/eden-cn/pkupenuhr/iosappid最终.png" width="500px" >


### **Step 4: Configure developer certificate**

1. Connect your mobile phone to the computer and select your iOS device in the `iOS Device` option.
    <img src="https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_e3283bb0262b4f267a32b88e02058206.png" width="500px" >

2. Log in to your Apple ID.<br>
2.1 Select **Xcode** **> Preferences** in the upper left corner on the Xcode page, or use the **Command** + shortcut to open Preferences.<br>
2.2 Select **Accounts**, click the Add button (+) in the lower-left corner, and select Apple ID to log in to your account.
    <img src="https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_d9320d09512c297e01802b9c61764b90.png" width="500px" >

3. Configure developer certificate.<br>
3.1 Click the `RTCSolution` project in the left navigation pane of Xcode, click the `RTCSolution` project under the `TARGETS` menu, and select **Signing & Capabilities > Automatically manage signing** to automatically generate the certificate.
    <img src="https://lf3-static.bytednsdoc.com/obj/eden-cn/pkupenuhr/8b11f97e-723f-4a37-a628-dadf3b9e0a96.png" width="500px" ><br>
3.2 Select Personal Team from the **Team** pop-up menu.<br>
    <img src="https://lf3-static.bytednsdoc.com/obj/eden-cn/pkupenuhr/54af18a8-8542-46f8-abb4-f421c7bcadcf.png" width="500px" >

3.3 **Change Bundle** **Identifier****.**   <br>
    The default `vertc.veRTCDemo.ios` has been registered. Change it to another Bundle ID in the format of `vertc.xxx`.
    <img src="https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_3f495e94b935f3e0ddf0f367d95d28bb.png" width="500px" >

### **Step 5: Compile and run**
Select **Product** > **Run** to compile the sample project. A new app will be added to your iOS device after the sample project is compiled. For a free Apple ID, you need to go to `Settings > General > VPN & Device Management > Description File & Device Management` to trust the developer app.<br>
<img src="https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_b29008057ebbd71e2fb401c27da79fea.png" width="500px" >


The following figure shows the screen when the app starts running.

<img src="https://portal.volccdn.com/obj/volcfe/cloud-universal-doc/upload_47fbb8962ec4906cb7b5e0c5cb0605fd.jpg" width="200px" >

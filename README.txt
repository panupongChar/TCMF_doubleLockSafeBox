กลุ่ม TCMF (กลุ่มที่ 4 : https://ecourse.cpe.ku.ac.th/tpm/project/practicum-63s)

ชื่อโครงงาน : Double Lock Safe Box
โครงงานนี้เป็นส่วนหนึ่งของรายวิชา 01204223 Practicum for Computer Engineering ภาคปลาย ปีการศึกษา 2563 หมู่ 11,12

รายชื่อผู้จัดทำ :
นายภาณุพงศ์ เจริญพร		6210501010	ภาควิชาวิศวกรรมคอมพิวเตอร์ คณะวิศวกรรมศาสตร์ มหาวิทยาลัยเกษตรศาสตร์
นายปพนธ์ ชุณหคล้าย		6210503691	ภาควิชาวิศวกรรมคอมพิวเตอร์ คณะวิศวกรรมศาสตร์ มหาวิทยาลัยเกษตรศาสตร์
นายสิทธิเจตน์ วงศ์ทิชาวัฒน์	6210503853	ภาควิชาวิศวกรรมคอมพิวเตอร์ คณะวิศวกรรมศาสตร์ มหาวิทยาลัยเกษตรศาสตร์
นายจิณณเจตน์ อจลพงศ์	6210505163	ภาควิชาวิศวกรรมคอมพิวเตอร์ คณะวิศวกรรมศาสตร์ มหาวิทยาลัยเกษตรศาสตร์

รายละเอียดไฟล์ :
TCMFproject
     |_____ SourceCode
     |                   |_____ Backend_TCMF
     |                   |                           |_____ backend.py (โค้ดที่ใช้รันไว้ตลอดเวลาบน raspberry pi โดยที่มีส่วนที่สร้างข้อความบันทึกใน Double_lock_safebox.log ด้วย)
     |                   |                           |_____ config.json (ใช้เก็บ password ที่ encrypt แล้ว)
     |                   |                           |_____ Double_lock_safebox.log (ใช้เก็บประวัติการพยายามเปิดตู้เซฟ)
     |                   |                           |_____ encrypt.py (ใช้ในการ encrypt รหัสผ่านที่จะตั้งขึ้นใหม่)
     |                   |                           |_____ shellScript_countFails.txt (ไฟล์นี้มีคำสั่ง ShellScript เพื่อการนับจำนวนครั้งที่มีการใส่รหัสผ่านผิดจากทั้งฮาร์ดแวร์และเว็บไซต์จากไฟล์ Double_lock_safebox.log)
     |                   |                           |_____ shellScript_findMostWrongInputPassword.txt (ไฟล์นี้มีคำสั่ง ShellScript เพื่อหารหัสผ่านที่ถูกส่งเข้ามาผิดและบ่อยที่สุดจากไฟล์ Double_lock_safebox.log)
     |                   |_____ Frontend_TCMF
     |                   |                           |_____ public_html
     |                   |                                                 |_____ index.html (โค้ดสำหรับแสดงหน้าเว็บใส่รหัสผ่าน)
     |                   |                                                 |_____ Enterpass.js (ใช้รับค่า check ที่ backend ตรวจสอบจาก hardware แล้วส่งมา และส่งรหัสที่ส่งจากหน้าเว็บไป backend ให้ backend ตรวจ)
     |                   |                                                 |_____ css
     |                   |                                                 |              |_____ bootstrap.min.css (เก็บ Scaffoldinggrid system จำนวน 12 คอลัมน์ สามารถเลือกใช้ได้ทั้งแบบ fixed และแบบ fluid, CSSstyle sheets สำหรับ html elements พื้นฐาน เช่น typography, tables, forms และ images , Componentsstyle sheets สำหรับสิ่งที่เราต้องใช้บ่อยๆ ไม่ว่าจะเป็น navigation, breadcrumbs รวมไปถึง pagination และย่อขนาดของไฟล์ลงโดยไม่ให้มีการขึ้นบรรทัดใหม่หรือการเว้นวรรคที่ไม่จำเป็น (.min))
     |                   |                                                 |              |_____ bootstrap.min.css.map (เป็นไฟล์ฟอร์แมต JSON ที่เชื่อมโยงไฟล์ CSS กับไฟล์ต้นฉบับ)
     |                   |                                                 |              |_____ Enterpass.css (เก็บ style พื้นฐานต่างๆ ที่กำหนดรูปแบบ ของเว็บ ได้แก่ สีของข้อความ สีพื้นหลัง ประเภทตัวอักษร และการจัดวางข้อความให้สวยงาม)
     |                   |                                                 |              |_____ util.css (เก็บ style ของ utility class ที่เก็บ padding ขนาดต่างๆไว้)
     |                   |                                                 |_____ favicon
     |                   |                                                 |              |_____ Home.ico (รูปไอคอนที่ใช้ตรงแท็บด้านบน)
     |                   |                                                 |              |_____ Security.ico (รูปไอคอนที่ใช้ตรงแท็บด้านบน)
     |                   |                                                 |_____ fonts
     |                   |                                                                |_____ montserrat (ไดเรคตอรีที่เก็บฟอนต์ montserrat ไว้)
     |                   |                                                                |_____ poppins (ไดเรคตอรีที่เก็บฟอนต์ poppinsไว้)
     |                   |                                                                |_____ fontawesome-webfont.svg (เก็บ icon & logo โดยที่เป็นรูปแบบของ vector เพื่อให้ขยายขนาดเท่าไรภาพก็ไม่แตก)
     |                   |                                                                |_____ fontawesome-webfont.woff2 (เป็นไฟล์ฟอนต์บนเว็บที่สร้างขึ้นในรูปแบบ WOFF (Web Open Font Format) 2.0 ซึ่งเป็นรูปแบบเปิดที่ใช้ในการส่งแบบอักษรของเว็บเพจได้ทันที มันถูกบันทึกเป็นคอนเทนเนอร์ที่บีบอัดซึ่งรองรับแบบอักษร TrueType ( .TTF ) และ OpenType ( .OTF ) ไฟล์ WOFF2 ยังรองรับเมตาดาต้าของลิขสิทธิ์แบบอักษร)
     |                   |_____ Hardware_TCMF
     |                                               |_____ project
     |                                                                     |_____ project.ino (โค้ดในการควบคุม microcontroller เขียนขึ้นด้วย ArduinoIDE 1.8.13)
     |                                                                     |_____ usbconfig.h (ไฟล์ configuration ของ USB driver บน practicum board ในการเชื่อมต่อกับ Raspberry Pi)
     |_____ Schematic
     |                   |_____ TCMF_DoubleLockSafeBox_PeriSchematic.png (รูปภาพผังวงจรฮาร์ดแวร์วาดด้วย easyEDA designer)
     |_____ ProjectImages
     |                   |_____ 6210501010_Panupong_Charoenporn.png (รูปภาพ นายภาณุพงศ์ เจริญพร คู่กับชิ้นงานโครงงาน)
     |                   |_____ 6210503691_Papon_Choonhaklai.png (รูปภาพ นายปพนธ์ ชุณหคล้าย คู่กับชิ้นงานโครงงาน)
     |                   |_____ 6210503853_Sittijed_Wongtichawat.png (รูปภาพ นายสิทธิเจตน์ วงศ์ทิชาวัฒน์ คู่กับชิ้นงานโครงงาน)
     |                   |_____ 6210505163_Jinnajate_Achalapong.png (รูปภาพ นายจิณณเจตน์ อจลพงศ์ คู่กับชิ้นงานโครงงาน)
     |                   |_____ projectPhotograph.png (รูปภาพชิ้นงานโครงงานโดยรวม)
     |                   |_____ TCMF_HardwareModel1.jpg (รูปภาพชิ้นงานโครงงานในส่วนฮารด์แวร์1)
     |                   |_____ TCMF_HardwareModel2.jpg (รูปภาพชิ้นงานโครงงานในส่วนฮารด์แวร์2)
     |                   |_____ websiteScreenshot.png (รูปภาพชิ้นงานโครงงานในส่วนหน้าเว็บ)
     |                   |_____ TCMF_DoubleLockSafeBox_StateDiagram.pdf (เอกสารประกอบการอธิบายสถานะการทำงานของ microcontroller)
     |                   |_____ HardwareLogo
     |                                               |_____ TCMF_DoubleLockSafeBox_Logo.png (รูปภาพตราสัญลักษณ์ที่ใช้ประกอบบนชิ้นงานโครงงาน)
     |                                               |_____ LogoFontUsed.txt (รายการฟอนต์ที่ใช้ในการทำรูปภาพตราสัญลักษณ์)
     |_____ README.txt (ไฟล์ระบุชื่อกลุ่ม ชื่อโครงงาน รายชื่อผู้จัดทำ รายละเอียดไฟล์ รายการไลบรารี/เฟรมเวิร์คที่ใช้ และ รายการอุปกรณ์ฮาร์ดแวร์ที่ใช้)
     |_____ License.txt (ไฟล์ระบุเงื่อนไขการอนุญาตให้ผู้อื่นนำงานนี้ไปใช้)

รายการไลบรารี/เฟรมเวิร์คที่ใช้ :
Backend - flask(by Armin Ronacher), flask_cors(by Armin Ronacher), datetime, hashlib, json, pyUSB, practicum(by Chaiporn Jaikaeo)
Frontend - Bootstrap(Framework by Mark Otto, Jacob Thornton)
Hardware - Arduino(library as framework), ArduinoBoard CPE-KU Practicum version 1.6.24 (by Chaiporn Jaikaeo), usbdrv.h(V-USB by obdev), Wire.h, Servo.h(by Michael Margolis, Arduino), LiquidCrystal_I2C.h(by Frank de Brabander)

รายการอุปกรณ์ฮาร์ดแวร์ที่ใช้ :
• Raspberry Pi 3 Model B+ พร้อม สาย Adapter Model YM-0530 1 ชุด
• Board NodeMCU - ATmega328p (Practicum Board v3.2 CPE. KU 2020-11) 1 ชุด
• Peripheral board (PRACTICUM PROTOBOARD CPE. KU) 2 ชิ้น
• สายแพ 3 สาย
• Jumper wire Female-Female 6 สาย
• Pin header ที่เพิ่มเข้ามา หลากหลายขนาด ดังนี้
- ขนาด 5x2 : 3 ชิ้น
- ขนาด 1x4 : 1 ชิ้น
- ขนาด 1x3 : 1 ชิ้น
- ขนาด 1x2 : 2 ชิ้น
• Switch button กดติดปล่อยดับแบบ 4 ขา ขนาด 6x6x5 mm 4 ชิ้น
• Switch button กดติดปล่อยดับแบบ 4 ขา ขนาด 6x6x7 mm 2 ชิ้น
• 1602 LCD (Blue Screen) 16x2 LCD with backlight of the LCD screen พร้อม I2CInterface 5V 1 ชุด
• Micro servo SG90 1 เครื่อง
• USB TTL PL2303TA 1 สาย
• Micro switch แบบยาว ขนาด 50 mm 220V 15A พร้อมบัดกรีสายไฟที่ขา C และ NO 1 ชิ้น
• Resistor 10k Ohm 1 ชิ้น
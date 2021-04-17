#ifndef OUTPUT_H
#define OUTPUT_H


/*
 * (testing [], insert, and get in MMap)
does not contain:
does not contain:
does not contain:
does not contain:
found: jan|5
does contain:
found: jan|5
does contain:
found: jan|5
does contain:
found: jan|5
does contain:
   [march|4]
   [jan|513]
[jan|5]
   [feb|28]
   [dec|3]


does not contain:
does not contain:
found: july|0
does contain:
found: july|0
does contain:
found: july|0
does contain:
   [march|4]
   [july|0]
[july|0]
   [jan|513]
[jan|5]
   [feb|28]
   [dec|3]


   (testing += operator)
does not contain:
does not contain:
does not contain:
does not contain:
this is TEMP :   jan|13
this is TEMP2 :   jan|2
      += operator  : jan|2
BPlusTree DTOR fired
BPlusTree DTOR fired
BPlusTree DTOR fired


this is TEMP :   jan|200
this is TEMP2 :   feb|23
      += operator  : Assertion failed!

     it asserted here because the keys were not the same!


     (testing find)
does contain:
found: dec|3
   [march|4]
   [jan|513]
[jan|5]
   [feb|28]
   [dec|3]


 */
#endif // OUTPUT_H

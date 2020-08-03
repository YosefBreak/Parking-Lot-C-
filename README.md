# Parking-Lot
C++ genric project which responsibale to manage a parking lot.

 
MtmParkingLot

תיאור כללי

בחלק מומש מערכת עבור מגרש חניה. 

מטרת המערכת היא מעקב אחר
כניסה/יציאה של רכבים למגרש, הדפסת מידע בעת הצורך, וטיפול בתשלום בהתאם לזמן החניה
וסוג הרכב.


• ישנם 3 סוגי רכבים הנתמכים במערכת, והם יכולים לחנות באיזורי חניה ספציפיים
)"בלוקים"( בהתאם לסוג הרכב:
1 .אופנועים יכולים לחנות בבלוק חניות לאופנועים בלבד
2 .רכב פרטי רגיל יכול לחנות בבלוק לרכבים פרטיים בלבד
3 .רכב של אדם נכה יכול לחנות בבלוק חניית נכים )בעדיפות ראשונה(, ובמידה והיא
מלאה גם בבלוק של רכבים פרטיים.

• מספר החניות בכל בלוק חניה )עבור אופנוע/רכב רגיל/חניות נכים( נקבע מראש בעת יצירת
מבנה מגרש החניה


תשלום של כל רכב נקבע לפי סוג הרכב וזמן החניה, בהתאם לחוקים הבאים:

o אופנוע ישלם 10 ש"ח עבור שעת חניה ראשונה או חלק ממנה, ו-5 ש"ח עבור כל
שעת חניה נוספת או חלק ממנה, וישלם לכל היותר על 6 שעות. לדוגמא:


▪ אופנוע שחנה במשך 3 דקות ישלם 10 ש"ח
▪ אופנוע שחנה במשך שעה )60 דקות( ישלם 10 ש"ח
▪ אופנוע שחנה במשך שעה ודקה ישלם 15 ש"ח
▪ אופנוע שחנה במשך 15 שעות ישלם 35 ש"ח )מחיר של 6 שעות(

• המערכת תומכת ב
1 .כניסת רכב למגרש החניה
2 .יציאה ותשלום של רכב ממגרש החניה
3 .הגעת הפקח למגרש החניה
4 .הדפסת כל הרכבים במגרש החניה

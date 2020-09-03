
(defrule 0_
(declare (salience 0))
(PlatformObj (var ?PlatformObj) (prop "Name") (relations "=") (values "PlatformObj_1") )
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "10") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "HK_1") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "25" crlf )
(printout t 权重：0 crlf ))

(defrule 1_
(declare (salience 0))
(PlatformObj (var ?PlatformObj) (prop "Name") (relations "=") (values "PlatformObj_2") )
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "10") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "HK_2") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "30" crlf )
(printout t 权重：0 crlf ))

(defrule 2_
(declare (salience 3))
(PlatformObj (var ?PlatformObj) (prop "sPosition") (relations "=") (values "1") )
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "20") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "HK_3") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_3" crlf )
(printout t 权重：3 crlf ))

(defrule 3_
(declare (salience 3))
(PlatformObj (var ?PlatformObj) (prop "sPosition") (relations "=") (values "3") )
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "22") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "HK_3") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
(printout t 权重：3 crlf ))

(defrule 4_
(declare (salience 4))
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "22") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "HK_3") )
(PlatformObj (var ?PlatformObj) (prop "sPosition") (relations "=") (values "4") )
 => 
(printout t ?PlatformObj "Name" "=" "55" crlf )
(printout t 权重：4 crlf ))

(defrule 5_
(declare (salience 5))
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "86") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "HK_1") )
(PlatformObj (var ?PlatformObj) (prop "sPosition") (relations "=") (values "3") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "15" crlf )
(printout t 权重：5 crlf ))

(defrule 6_
(declare (salience 5))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "15") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "15456" crlf )
(printout t 权重：5 crlf ))

(defrule 7_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "255") )
(PlatformObj (var "PlatformObj") (prop "ID") (relations "=") (values "584") )
(PlatformObj (var "") (prop "") (relations "") (values "") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
(printout t 权重：0 crlf ))

(defrule 8_
(declare (salience 5))
(PlatformObj (var "PlatformObj") (prop "Enemy") (relations "=") (values "Enum_att_1") )
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "255") )
 => 
(printout t "InterNissCmd" "dSitime" "=" "2555" crlf )
(printout t 权重：5 crlf ))

(defrule 9_
(declare (salience 4))
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "255") )
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations "=") (values "35") )
 => 
(printout t "InterNissCmd" "dLon" "=" "566" crlf )
(printout t 权重：4 crlf ))

(defrule 10_
(declare (salience 4))
(PlatformObj (var "PlatformObj") (prop "ID") (relations "=") (values "85") )
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations "=") (values "35") )
 => 
(printout t "InterNissCmd" "dLon" "=" "5667" crlf )
(printout t 权重：4 crlf ))

(defrule 11_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "25") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "26" crlf )
(printout t 权重：0 crlf ))

(defrule 12_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "25") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "25" crlf )
(printout t 权重：0 crlf ))

(defrule 13_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "aa") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "bb" crlf )
(printout t 权重：0 crlf ))

(defrule 14_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations ">") (values "56") )
(PlatformObj (var "PlatformObj") (prop "Enum_sur_state") (relations "=") (values "Enum_sur_0") )
 => 
(printout t "InterNissCmd" "dLon" "=" "2555" crlf )
(printout t 权重：0 crlf ))

(defrule 15_
(declare (salience 3))
(PlatformObj (var "PlatformObj") (prop "Enum_sur_state") (relations "=") (values "Enum_sur_1") )
(PlatformObj (var "PlatformObj") (prop "Type") (relations "=") (values "2584") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_3" crlf )
(printout t 权重：3 crlf ))

(defrule 16_
(declare (salience 3))
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations "=") (values "50") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_3" crlf )
(printout t 权重：3 crlf ))

(defrule 17_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "2") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "25" crlf )
(printout t 权重：0 crlf ))

(defrule 18_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "2") )
 => 
(printout t "InterNissCmd" "SendID" "=" "2" crlf )
(printout t 权重：0 crlf ))

(defrule 19_
(declare (salience 4))
(PlatformObj (var "InterNissCmd") (prop "dSitime") (relations "=") (values "25") )
 => 
(printout t "PlatformObj" "Name" "=" "55" crlf )
(printout t 权重：4 crlf ))

(defrule 20_
(declare (salience 5))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "po") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
(printout t 权重：5 crlf ))

(defrule 21_
(declare (salience 5))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "po") )
 => 
(printout t "InterNissCmd" "dLon" "=" "25" crlf )
(printout t 权重：5 crlf ))

(defrule 22_
(declare (salience 5))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "15") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
(printout t 权重：5 crlf ))

(defrule 23_
(declare (salience 5))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "15") )
 => 
(printout t "InterNissCmd" "dLon" "=" "25" crlf )
(printout t 权重：5 crlf ))

(defrule 24_
(declare (salience 22))
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "255") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
(printout t 权重：22 crlf ))

(defrule 25_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Work_timeworktime_start") (relations "=") (values "255") )
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations ">") (values "23") )
 => 
(printout t "InterNissCmd" "dSitime" "=" "255" crlf )
(printout t 权重：0 crlf ))

(defrule 26_
(declare (salience 5))
(PlatformObj (var "PlatformObj") (prop "Enemy") (relations "=") (values "Enum_att_1") )
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "255") )
 => 
(printout t "InterNissCmd" "dSitime" "=" "2555" crlf )
(printout t 权重：5 crlf ))

(defrule 27_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "2.22") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "2.22" crlf )
(printout t 权重：0 crlf ))

(defrule 28_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Enemy") (relations "=") (values "绾㈡柟") )
(PlatformObj (var "PlatformObj") (prop "Work_timeworktime_end") (relations "=") (values "255") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
(printout t 权重：0 crlf ))

(defrule 29_
(declare (salience 2))
(PlatformObj (var "PlatformObj") (prop "Work_timeworktime_start") (relations "=") (values "255") )
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations ">") (values "18") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "56" crlf )
(printout t 权重：2 crlf ))

(defrule 30_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "29") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "28" crlf )
(printout t 权重：0 crlf ))

(defrule 31_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "35") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "35" crlf )
(printout t 权重：0 crlf ))

(defrule 32_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "aabb") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "bbcc" crlf )
(printout t 权重：0 crlf ))

(defrule 33_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations ">") (values "66") )
(PlatformObj (var "PlatformObj") (prop "Enum_sur_state") (relations "=") (values "Enum_sur_0") )
 => 
(printout t "InterNissCmd" "dLon" "=" "255" crlf )
(printout t 权重：0 crlf ))

(defrule 34_
(declare (salience 3))
(PlatformObj (var ?PlatformObj) (prop "Enum_sur_state") (relations "=") (values "Enum_sur_1") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "2564") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_100" crlf )
(printout t 权重：3 crlf ))

(defrule 35_
(declare (salience 3))
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations "=") (values "50") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_3" crlf )
(printout t 权重：3 crlf ))

(defrule 36_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "4") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "35" crlf )
(printout t 权重：0 crlf ))

(defrule 37_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "4") )
 => 
(printout t "InterNissCmd" "SendID" "=" "4" crlf )
(printout t 权重：0 crlf ))

(defrule 38_
(declare (salience 4))
(PlatformObj (var "InterNissCmd") (prop "dSitime") (relations "=") (values "35") )
 => 
(printout t "PlatformObj" "Name" "=" "65" crlf )
(printout t 权重：4 crlf ))

(defrule 39_
(declare (salience 5))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "po_1") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
(printout t 权重：5 crlf ))

(defrule 40_
(declare (salience 5))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "po_2") )
 => 
(printout t "InterNissCmd" "dLon" "=" "25" crlf )
(printout t 权重：5 crlf ))

(defrule 41_
(declare (salience 5))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "25") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
(printout t 权重：5 crlf ))

(defrule 42_
(declare (salience 5))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "25") )
 => 
(printout t "InterNissCmd" "dLon" "=" "35" crlf )
(printout t 权重：5 crlf ))

(defrule 43_
(declare (salience 22))
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "256") )
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "26") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
(printout t 权重：22 crlf ))

(defrule 44_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Work_timeworktime_start") (relations "=") (values "256") )
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations ">") (values "23") )
 => 
(printout t "InterNissCmd" "dSitime" "=" "252" crlf )
(printout t 权重：0 crlf ))

(defrule 45_
(declare (salience 5))
(PlatformObj (var "PlatformObj") (prop "Enemy") (relations "=") (values "Enum_att_1") )
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "252") )
 => 
(printout t "InterNissCmd" "dSitime" "=" "2548" crlf )
(printout t 权重：5 crlf ))

(defrule 46_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "2.44") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "2.44" crlf )
(printout t 权重：0 crlf ))

(defrule 47_
(declare (salience 0))
(PlatformObj (var "PlatformObj") (prop "Enemy") (relations "=") (values "绾㈡柟") )
(PlatformObj (var "PlatformObj") (prop "Work_timeworktime_end") (relations "=") (values "255") )
 => 
(printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
(printout t 权重：0 crlf ))

(defrule 48_
(declare (salience 2))
(PlatformObj (var "PlatformObj") (prop "Work_timeworktime_start") (relations "=") (values "256") )
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations ">") (values "20") )
 => 
(printout t "InterNissCmd" "RecieveID" "=" "66" crlf )
(printout t 权重：2 crlf ))


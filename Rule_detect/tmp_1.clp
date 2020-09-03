
(defrule 0_
(PlatformObj (var ?PlatformObj) (prop "Name") (relations "=") (values "PlatformObj_1") )
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "10") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "HK_1") )
 => (printout t "InterNissCmd" "RecieveID" "=" "25" crlf )
)

(defrule 1_
(PlatformObj (var ?PlatformObj) (prop "Name") (relations "=") (values "PlatformObj_2") )
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "10") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "HK_2") )
 => (printout t "InterNissCmd" "RecieveID" "=" "30" crlf )
)

(defrule 2_
(PlatformObj (var ?PlatformObj) (prop "sPosition") (relations "=") (values "1") )
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "20") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "HK_3") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_3" crlf )
)

(defrule 3_
(PlatformObj (var ?PlatformObj) (prop "sPosition") (relations "=") (values "3") )
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "22") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "HK_3") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
)

(defrule 4_
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "22") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "HK_3") )
(PlatformObj (var ?PlatformObj) (prop "sPosition") (relations "=") (values "4") )
 => (printout t ?PlatformObj "Name" "=" "55" crlf )
)

(defrule 5_
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "86") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "HK_1") )
(PlatformObj (var ?PlatformObj) (prop "sPosition") (relations "=") (values "3") )
 => (printout t "InterNissCmd" "RecieveID" "=" "15" crlf )
)

(defrule 6_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "15") )
 => (printout t "InterNissCmd" "RecieveID" "=" "15456" crlf )
)

(defrule 7_
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "255") )
(PlatformObj (var "PlatformObj") (prop "ID") (relations "=") (values "584") )
(PlatformObj (var "") (prop "") (relations "") (values "") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
)

(defrule 8_
(PlatformObj (var "PlatformObj") (prop "Enemy") (relations "=") (values "Enum_att_1") )
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "255") )
 => (printout t "InterNissCmd" "dSitime" "=" "2555" crlf )
)

(defrule 9_
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "255") )
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations "=") (values "35") )
 => (printout t "InterNissCmd" "dLon" "=" "566" crlf )
)

(defrule 10_
(PlatformObj (var "PlatformObj") (prop "ID") (relations "=") (values "85") )
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations "=") (values "35") )
 => (printout t "InterNissCmd" "dLon" "=" "5667" crlf )
)

(defrule 11_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "25") )
 => (printout t "InterNissCmd" "RecieveID" "=" "26" crlf )
)

(defrule 12_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "25") )
 => (printout t "InterNissCmd" "RecieveID" "=" "25" crlf )
)

(defrule 13_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "aa") )
 => (printout t "InterNissCmd" "RecieveID" "=" "bb" crlf )
)

(defrule 14_
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations ">") (values "56") )
(PlatformObj (var "PlatformObj") (prop "Enum_sur_state") (relations "=") (values "Enum_sur_0") )
 => (printout t "InterNissCmd" "dLon" "=" "2555" crlf )
)

(defrule 15_
(PlatformObj (var "PlatformObj") (prop "Enum_sur_state") (relations "=") (values "Enum_sur_1") )
(PlatformObj (var "PlatformObj") (prop "Type") (relations "=") (values "2584") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_3" crlf )
)

(defrule 16_
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations "=") (values "50") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_3" crlf )
)

(defrule 17_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "2") )
 => (printout t "InterNissCmd" "RecieveID" "=" "25" crlf )
)

(defrule 18_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "2") )
 => (printout t "InterNissCmd" "SendID" "=" "2" crlf )
)

(defrule 19_
(PlatformObj (var "InterNissCmd") (prop "dSitime") (relations "=") (values "25") )
 => (printout t "PlatformObj" "Name" "=" "55" crlf )
)

(defrule 20_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "po") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
)

(defrule 21_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "po") )
 => (printout t "InterNissCmd" "dLon" "=" "25" crlf )
)

(defrule 22_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "15") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
)

(defrule 23_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "15") )
 => (printout t "InterNissCmd" "dLon" "=" "25" crlf )
)

(defrule 24_
(PlatformObj (var ?PlatformObj) (prop "Send1ID") (relations "=") (values "255") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
)

(defrule 25_
(PlatformObj (var "PlatformObj") (prop "Work_timeworktime_start") (relations "=") (values "255") )
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations ">") (values "23") )
 => (printout t "InterNissCmd" "dSitime" "=" "255" crlf )
)

(defrule 26_
(PlatformObj (var "PlatformObj") (prop "Enemy") (relations "=") (values "Enum_att_1") )
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "255") )
 => (printout t "InterNissCmd" "dSitime" "=" "2555" crlf )
)

(defrule 27_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "2.22") )
 => (printout t "InterNissCmd" "RecieveID" "=" "2.22" crlf )
)

(defrule 28_
(PlatformObj (var "PlatformObj") (prop "Enemy") (relations "=") (values "红方") )
(PlatformObj (var "PlatformObj") (prop "Work_timeworktime_end") (relations "=") (values "255") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
)

(defrule 29_
(PlatformObj (var "PlatformObj") (prop "Work_timeworktime_start") (relations "=") (values "255") )
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations ">") (values "18") )
 => (printout t "InterNissCmd" "RecieveID" "=" "56" crlf )
)

(defrule 30_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "29") )
 => (printout t "InterNissCmd" "RecieveID" "=" "28" crlf )
)

(defrule 31_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "35") )
 => (printout t "InterNissCmd" "RecieveID" "=" "35" crlf )
)

(defrule 32_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "aabb") )
 => (printout t "InterNissCmd" "RecieveID" "=" "bbcc" crlf )
)

(defrule 33_
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations ">") (values "66") )
(PlatformObj (var "PlatformObj") (prop "Enum_sur_state") (relations "=") (values "Enum_sur_0") )
 => (printout t "InterNissCmd" "dLon" "=" "255" crlf )
)

(defrule 34_
(PlatformObj (var ?PlatformObj) (prop "Enum_sur_state") (relations "=") (values "Enum_sur_1") )
(PlatformObj (var ?PlatformObj) (prop "Type") (relations "=") (values "2564") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_100" crlf )
)

(defrule 35_
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations "=") (values "50") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_3" crlf )
)

(defrule 36_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "4") )
 => (printout t "InterNissCmd" "RecieveID" "=" "35" crlf )
)

(defrule 37_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "4") )
 => (printout t "InterNissCmd" "SendID" "=" "4" crlf )
)

(defrule 38_
(PlatformObj (var "InterNissCmd") (prop "dSitime") (relations "=") (values "35") )
 => (printout t "PlatformObj" "Name" "=" "65" crlf )
)

(defrule 39_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "po_1") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
)

(defrule 40_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "po_2") )
 => (printout t "InterNissCmd" "dLon" "=" "25" crlf )
)

(defrule 41_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "25") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
)

(defrule 42_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "25") )
 => (printout t "InterNissCmd" "dLon" "=" "35" crlf )
)

(defrule 43_
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "256") )
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "26") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
)

(defrule 44_
(PlatformObj (var "PlatformObj") (prop "Work_timeworktime_start") (relations "=") (values "256") )
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations ">") (values "23") )
 => (printout t "InterNissCmd" "dSitime" "=" "252" crlf )
)

(defrule 45_
(PlatformObj (var "PlatformObj") (prop "Enemy") (relations "=") (values "Enum_att_1") )
(PlatformObj (var "PlatformObj") (prop "Send1ID") (relations "=") (values "252") )
 => (printout t "InterNissCmd" "dSitime" "=" "2548" crlf )
)

(defrule 46_
(PlatformObj (var "PlatformObj") (prop "Name") (relations "=") (values "2.44") )
 => (printout t "InterNissCmd" "RecieveID" "=" "2.44" crlf )
)

(defrule 47_
(PlatformObj (var "PlatformObj") (prop "Enemy") (relations "=") (values "红方") )
(PlatformObj (var "PlatformObj") (prop "Work_timeworktime_end") (relations "=") (values "255") )
 => (printout t "InterNissCmd" "Work_timeEnum_time" "=" "Enum_time_1" crlf )
)

(defrule 48_
(PlatformObj (var "PlatformObj") (prop "Work_timeworktime_start") (relations "=") (values "256") )
(PlatformObj (var "PlatformObj") (prop "sPosition") (relations ">") (values "20") )
 => (printout t "InterNissCmd" "RecieveID" "=" "66" crlf )
)


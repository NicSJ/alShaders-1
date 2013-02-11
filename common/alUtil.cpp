#include "alUtil.h"

void alphaInversion( const AtRGB& scatterColour, float scatterDist, AtRGB& sigma_s_prime_,
                                                                             AtRGB& sigma_a_ )
{
       AtRGB col = scatterColour;

       col = col / maxh(col);

       AtRGB alpha_prime = rgb(alpha1_3(clamp(col.r*.439, 0, 1)),
                                   alpha1_3(clamp(col.g*.439, 0, 1)),
                                   alpha1_3(clamp(col.b*.439, 0, 1 )) );

       AtRGB sigma_tr = rgb(1.0f,1.0f,1.0f) / (scatterColour * col);


       AtRGB sigma_t_prime = rgb(  sigma_tr[0] / ( sqrt( 3 * ( 1 - alpha_prime[0] ) ) ),
                                   sigma_tr[1] / ( sqrt( 3 * ( 1 - alpha_prime[1] ) ) ),
                                   sigma_tr[2] / ( sqrt( 3 * ( 1 - alpha_prime[2] ) ) ) );

       sigma_s_prime_ = sigma_t_prime * alpha_prime;
       sigma_a_ = sigma_t_prime - sigma_s_prime_;
}

float alpha1_3( float x )
{
       /* Discrete looking up tables for alpha, the average is 0.877051679 */
       float alpha1_3[2001] = {
       0.00000000,   0.00558923,   0.01115797,   0.01665007,   0.02210481,
       0.02750112,   0.03284671,   0.03814856,   0.04338977,   0.04859844,
       0.05373995,   0.05885673,   0.06390312,   0.06892926,   0.07388504,
       0.07882177,   0.08369136,   0.08853990,   0.09332764,   0.09808919,
       0.10279935,   0.10747508,   0.11211185,   0.11670291,   0.12127043,
       0.12577795,   0.13028026,   0.13470538,   0.13913050,   0.14349029,
       0.14783410,   0.15213769,   0.15640127,   0.16065252,   0.16483694,
       0.16902137,   0.17314595,   0.17725226,   0.18133307,   0.18536231,
       0.18939154,   0.19335619,   0.19730936,   0.20123855,   0.20511665,
       0.20899475,   0.21281796,   0.21662198,   0.22041780,   0.22414869,
       0.22787959,   0.23157933,   0.23523805,   0.23889677,   0.24250574,
       0.24609323,   0.24968071,   0.25320414,   0.25672132,   0.26023378,
       0.26368154,   0.26712930,   0.27056560,   0.27394484,   0.27732408,
       0.28068924,   0.28400083,   0.28731243,   0.29061143,   0.29385624,
       0.29710105,   0.30033883,   0.30351770,   0.30669657,   0.30987544,
       0.31299175,   0.31610551,   0.31921927,   0.32228487,   0.32533434,
       0.32838381,   0.33140345,   0.33438944,   0.33737543,   0.34035383,
       0.34327712,   0.34620042,   0.34912372,   0.35200366,   0.35486504,
       0.35772642,   0.36057524,   0.36337547,   0.36617570,   0.36897593,
       0.37173785,   0.37447768,   0.37721751,   0.37995734,   0.38263844,
       0.38531861,   0.38799878,   0.39066402,   0.39328525,   0.39590648,
       0.39852771,   0.40112343,   0.40368644,   0.40624945,   0.40881246,
       0.41134459,   0.41385008,   0.41635557,   0.41886105,   0.42133554,
       0.42378419,   0.42623284,   0.42868149,   0.43110422,   0.43349670,
       0.43588919,   0.43828168,   0.44065853,   0.44299552,   0.44533251,
       0.44766950,   0.45000634,   0.45228848,   0.45457062,   0.45685277,
       0.45913491,   0.46138339,   0.46361132,   0.46583925,   0.46806719,
       0.47028802,   0.47246237,   0.47463672,   0.47681107,   0.47898542,
       0.48113151,   0.48325289,   0.48537427,   0.48749565,   0.48961703,
       0.49169550,   0.49376451,   0.49583352,   0.49790253,   0.49997155,
       0.50198950,   0.50400673,   0.50602397,   0.50804120,   0.51005696,
       0.51202300,   0.51398903,   0.51595507,   0.51792111,   0.51988715,
       0.52180546,   0.52372087,   0.52563628,   0.52755168,   0.52946709,
       0.53134636,   0.53321169,   0.53507702,   0.53694235,   0.53880768,
       0.54065514,   0.54247094,   0.54428674,   0.54610254,   0.54791834,
       0.54973414,   0.55150812,   0.55327492,   0.55504172,   0.55680852,
       0.55857532,   0.56033273,   0.56205105,   0.56376937,   0.56548769,
       0.56720601,   0.56892433,   0.57062471,   0.57229506,   0.57396541,
       0.57563576,   0.57730611,   0.57897646,   0.58062843,   0.58225130,
       0.58387418,   0.58549706,   0.58711994,   0.58874281,   0.59035510,
       0.59193100,   0.59350689,   0.59508278,   0.59665867,   0.59823456,
       0.59981045,   0.60134542,   0.60287480,   0.60440418,   0.60593356,
       0.60746294,   0.60899232,   0.61050599,   0.61198933,   0.61347266,
       0.61495599,   0.61643932,   0.61792265,   0.61940599,   0.62086198,
       0.62229972,   0.62373746,   0.62517519,   0.62661293,   0.62805067,
       0.62948840,   0.63089705,   0.63228964,   0.63368222,   0.63507481,
       0.63646739,   0.63785997,   0.63925256,   0.64062442,   0.64197228,
       0.64332014,   0.64466800,   0.64601586,   0.64736372,   0.64871158,
       0.65005749,   0.65136105,   0.65266461,   0.65396816,   0.65527172,
       0.65657528,   0.65787883,   0.65918239,   0.66046959,   0.66172925,
       0.66298891,   0.66424858,   0.66550824,   0.66676790,   0.66802756,
       0.66928723,   0.67052801,   0.67174417,   0.67296034,   0.67417651,
       0.67539268,   0.67660884,   0.67782501,   0.67904118,   0.68024822,
       0.68142128,   0.68259434,   0.68376740,   0.68494046,   0.68611352,
       0.68728658,   0.68845964,   0.68963270,   0.69077641,   0.69190674,
       0.69303707,   0.69416740,   0.69529773,   0.69642806,   0.69755839,
       0.69868872,   0.69981905,   0.70091380,   0.70200177,   0.70308974,
       0.70417771,   0.70526568,   0.70635365,   0.70744162,   0.70852959,
       0.70961756,   0.71067829,   0.71172426,   0.71277022,   0.71381619,
       0.71486216,   0.71590812,   0.71695409,   0.71800006,   0.71904602,
       0.72008833,   0.72109264,   0.72209696,   0.72310127,   0.72410559,
       0.72510990,   0.72611422,   0.72711853,   0.72812285,   0.72912716,
       0.73012607,   0.73108907,   0.73205207,   0.73301508,   0.73397808,
       0.73494109,   0.73590409,   0.73686709,   0.73783010,   0.73879310,
       0.73975611,   0.74068851,   0.74161054,   0.74253256,   0.74345459,
       0.74437662,   0.74529864,   0.74622067,   0.74714270,   0.74806473,
       0.74898675,   0.74990878,   0.75079418,   0.75167555,   0.75255693,
       0.75343831,   0.75431968,   0.75520106,   0.75608243,   0.75696381,
       0.75784519,   0.75872656,   0.75960794,   0.76046693,   0.76130797,
       0.76214902,   0.76299006,   0.76383111,   0.76467216,   0.76551320,
       0.76635425,   0.76719530,   0.76803634,   0.76887739,   0.76971843,
       0.77053286,   0.77133389,   0.77213492,   0.77293595,   0.77373699,
       0.77453802,   0.77533905,   0.77614008,   0.77694111,   0.77774214,
       0.77854317,   0.77934420,   0.78013804,   0.78089936,   0.78166069,
       0.78242202,   0.78318335,   0.78394467,   0.78470600,   0.78546733,
       0.78622866,   0.78698998,   0.78775131,   0.78851264,   0.78927397,
       0.79003347,   0.79075540,   0.79147733,   0.79219927,   0.79292120,
       0.79364313,   0.79436506,   0.79508700,   0.79580893,   0.79653086,
       0.79725279,   0.79797473,   0.79869666,   0.79941859,   0.80013292,
       0.80081576,   0.80149861,   0.80218145,   0.80286430,   0.80354714,
       0.80422999,   0.80491284,   0.80559568,   0.80627853,   0.80696137,
       0.80764422,   0.80832706,   0.80900991,   0.80969276,   0.81035427,
       0.81099834,   0.81164241,   0.81228648,   0.81293055,   0.81357461,
       0.81421868,   0.81486275,   0.81550682,   0.81615089,   0.81679495,
       0.81743902,   0.81808309,   0.81872716,   0.81937123,   0.82001438,
       0.82061999,   0.82122559,   0.82183119,   0.82243680,   0.82304240,
       0.82364800,   0.82425361,   0.82485921,   0.82546481,   0.82607042,
       0.82667602,   0.82728162,   0.82788723,   0.82849283,   0.82909844,
       0.82970404,   0.83029014,   0.83085760,   0.83142506,   0.83199251,
       0.83255997,   0.83312743,   0.83369489,   0.83426235,   0.83482981,
       0.83539727,   0.83596472,   0.83653218,   0.83709964,   0.83766710,
       0.83823456,   0.83880202,   0.83936947,   0.83993693,   0.84047078,
       0.84100042,   0.84153006,   0.84205970,   0.84258935,   0.84311899,
       0.84364863,   0.84417827,   0.84470792,   0.84523756,   0.84576720,
       0.84629684,   0.84682648,   0.84735613,   0.84788577,   0.84841541,
       0.84894505,   0.84947470,   0.85000403,   0.85049620,   0.85098837,
       0.85148054,   0.85197271,   0.85246487,   0.85295704,   0.85344921,
       0.85394138,   0.85443355,   0.85492572,   0.85541789,   0.85591006,
       0.85640222,   0.85689439,   0.85738656,   0.85787873,   0.85837090,
       0.85886307,   0.85935524,   0.85984740,   0.86031397,   0.86076902,
       0.86122408,   0.86167913,   0.86213419,   0.86258924,   0.86304430,
       0.86349935,   0.86395441,   0.86440946,   0.86486452,   0.86531957,
       0.86577463,   0.86622969,   0.86668474,   0.86713980,   0.86759485,
       0.86804991,   0.86850496,   0.86896002,   0.86941507,   0.86987013,
       0.87029894,   0.87071726,   0.87113559,   0.87155391,   0.87197224,
       0.87239056,   0.87280889,   0.87322721,   0.87364554,   0.87406386,
       0.87448219,   0.87490051,   0.87531884,   0.87573716,   0.87615549,
       0.87657381,   0.87699214,   0.87741046,   0.87782879,   0.87824711,
       0.87866544,   0.87908376,   0.87950209,   0.87992041,   0.88030933,
       0.88069134,   0.88107334,   0.88145535,   0.88183735,   0.88221936,
       0.88260137,   0.88298337,   0.88336538,   0.88374739,   0.88412939,
       0.88451140,   0.88489341,   0.88527541,   0.88565742,   0.88603943,
       0.88642143,   0.88680344,   0.88718545,   0.88756745,   0.88794946,
       0.88833146,   0.88871347,   0.88909548,   0.88947748,   0.88985949,
       0.89021882,   0.89056495,   0.89091109,   0.89125722,   0.89160336,
       0.89194949,   0.89229563,   0.89264176,   0.89298789,   0.89333403,
       0.89368016,   0.89402630,   0.89437243,   0.89471857,   0.89506470,
       0.89541084,   0.89575697,   0.89610310,   0.89644924,   0.89679537,
       0.89714151,   0.89748764,   0.89783378,   0.89817991,   0.89852605,
       0.89887218,   0.89921831,   0.89956445,   0.89991058,   0.90023048,
       0.90054123,   0.90085198,   0.90116273,   0.90147348,   0.90178423,
       0.90209498,   0.90240573,   0.90271648,   0.90302724,   0.90333799,
       0.90364874,   0.90395949,   0.90427024,   0.90458099,   0.90489174,
       0.90520249,   0.90551324,   0.90582400,   0.90613475,   0.90644550,
       0.90675625,   0.90706700,   0.90737775,   0.90768850,   0.90799925,
       0.90831000,   0.90862076,   0.90893151,   0.90924226,   0.90955301,
       0.90986376,   0.91015494,   0.91043085,   0.91070676,   0.91098266,
       0.91125857,   0.91153447,   0.91181038,   0.91208629,   0.91236219,
       0.91263810,   0.91291401,   0.91318991,   0.91346582,   0.91374173,
       0.91401763,   0.91429354,   0.91456945,   0.91484535,   0.91512126,
       0.91539716,   0.91567307,   0.91594898,   0.91622488,   0.91650079,
       0.91677670,   0.91705260,   0.91732851,   0.91760442,   0.91788032,
       0.91815623,   0.91843213,   0.91870804,   0.91898395,   0.91925985,
       0.91953576,   0.91981167,   0.92007670,   0.92031836,   0.92056002,
       0.92080168,   0.92104333,   0.92128499,   0.92152665,   0.92176831,
       0.92200997,   0.92225162,   0.92249328,   0.92273494,   0.92297660,
       0.92321826,   0.92345992,   0.92370157,   0.92394323,   0.92418489,
       0.92442655,   0.92466821,   0.92490986,   0.92515152,   0.92539318,
       0.92563484,   0.92587650,   0.92611815,   0.92635981,   0.92660147,
       0.92684313,   0.92708479,   0.92732644,   0.92756810,   0.92780976,
       0.92805142,   0.92829308,   0.92853473,   0.92877639,   0.92901805,
       0.92925971,   0.92950137,   0.92974302,   0.92998468,   0.93019488,
       0.93040295,   0.93061103,   0.93081910,   0.93102717,   0.93123524,
       0.93144331,   0.93165138,   0.93185945,   0.93206752,   0.93227560,
       0.93248367,   0.93269174,   0.93289981,   0.93310788,   0.93331595,
       0.93352402,   0.93373209,   0.93394017,   0.93414824,   0.93435631,
       0.93456438,   0.93477245,   0.93498052,   0.93518859,   0.93539667,
       0.93560474,   0.93581281,   0.93602088,   0.93622895,   0.93643702,
       0.93664509,   0.93685316,   0.93706124,   0.93726931,   0.93747738,
       0.93768545,   0.93789352,   0.93810159,   0.93830966,   0.93851773,
       0.93872581,   0.93893388,   0.93914195,   0.93935002,   0.93955809,
       0.93976616,   0.93997423,   0.94015352,   0.94032873,   0.94050395,
       0.94067917,   0.94085438,   0.94102960,   0.94120482,   0.94138003,
       0.94155525,   0.94173046,   0.94190568,   0.94208090,   0.94225611,
       0.94243133,   0.94260655,   0.94278176,   0.94295698,   0.94313219,
       0.94330741,   0.94348263,   0.94365784,   0.94383306,   0.94400827,
       0.94418349,   0.94435871,   0.94453392,   0.94470914,   0.94488436,
       0.94505957,   0.94523479,   0.94541000,   0.94558522,   0.94576044,
       0.94593565,   0.94611087,   0.94628608,   0.94646130,   0.94663652,
       0.94681173,   0.94698695,   0.94716217,   0.94733738,   0.94751260,
       0.94768781,   0.94786303,   0.94803825,   0.94821346,   0.94838868,
       0.94856389,   0.94873911,   0.94891433,   0.94908954,   0.94926476,
       0.94943998,   0.94961519,   0.94979041,   0.94996562,   0.95011507,
       0.95025823,   0.95040139,   0.95054455,   0.95068771,   0.95083088,
       0.95097404,   0.95111720,   0.95126036,   0.95140352,   0.95154668,
       0.95168984,   0.95183300,   0.95197616,   0.95211932,   0.95226248,
       0.95240564,   0.95254880,   0.95269196,   0.95283512,   0.95297828,
       0.95312144,   0.95326460,   0.95340776,   0.95355092,   0.95369408,
       0.95383724,   0.95398040,   0.95412356,   0.95426672,   0.95440988,
       0.95455304,   0.95469620,   0.95483936,   0.95498252,   0.95512568,
       0.95526885,   0.95541201,   0.95555517,   0.95569833,   0.95584149,
       0.95598465,   0.95612781,   0.95627097,   0.95641413,   0.95655729,
       0.95670045,   0.95684361,   0.95698677,   0.95712993,   0.95727309,
       0.95741625,   0.95755941,   0.95770257,   0.95784573,   0.95798889,
       0.95813205,   0.95827521,   0.95841837,   0.95856153,   0.95870469,
       0.95884785,   0.95899101,   0.95913417,   0.95927733,   0.95942049,
       0.95956365,   0.95970682,   0.95984998,   0.95999314,   0.96010658,
       0.96021853,   0.96033048,   0.96044243,   0.96055438,   0.96066633,
       0.96077828,   0.96089022,   0.96100217,   0.96111412,   0.96122607,
       0.96133802,   0.96144997,   0.96156192,   0.96167387,   0.96178582,
       0.96189777,   0.96200971,   0.96212166,   0.96223361,   0.96234556,
       0.96245751,   0.96256946,   0.96268141,   0.96279336,   0.96290531,
       0.96301726,   0.96312920,   0.96324115,   0.96335310,   0.96346505,
       0.96357700,   0.96368895,   0.96380090,   0.96391285,   0.96402480,
       0.96413675,   0.96424869,   0.96436064,   0.96447259,   0.96458454,
       0.96469649,   0.96480844,   0.96492039,   0.96503234,   0.96514429,
       0.96525624,   0.96536818,   0.96548013,   0.96559208,   0.96570403,
       0.96581598,   0.96592793,   0.96603988,   0.96615183,   0.96626378,
       0.96637573,   0.96648768,   0.96659962,   0.96671157,   0.96682352,
       0.96693547,   0.96704742,   0.96715937,   0.96727132,   0.96738327,
       0.96749522,   0.96760717,   0.96771911,   0.96783106,   0.96794301,
       0.96805496,   0.96816691,   0.96827886,   0.96839081,   0.96850276,
       0.96861471,   0.96872666,   0.96883860,   0.96895055,   0.96906250,
       0.96917445,   0.96928640,   0.96939835,   0.96951030,   0.96962225,
       0.96973420,   0.96984615,   0.96995809,   0.97005102,   0.97013256,
       0.97021410,   0.97029564,   0.97037719,   0.97045873,   0.97054027,
       0.97062181,   0.97070335,   0.97078490,   0.97086644,   0.97094798,
       0.97102952,   0.97111106,   0.97119261,   0.97127415,   0.97135569,
       0.97143723,   0.97151877,   0.97160031,   0.97168186,   0.97176340,
       0.97184494,   0.97192648,   0.97200802,   0.97208957,   0.97217111,
       0.97225265,   0.97233419,   0.97241573,   0.97249728,   0.97257882,
       0.97266036,   0.97274190,   0.97282344,   0.97290499,   0.97298653,
       0.97306807,   0.97314961,   0.97323115,   0.97331269,   0.97339424,
       0.97347578,   0.97355732,   0.97363886,   0.97372040,   0.97380195,
       0.97388349,   0.97396503,   0.97404657,   0.97412811,   0.97420966,
       0.97429120,   0.97437274,   0.97445428,   0.97453582,   0.97461737,
       0.97469891,   0.97478045,   0.97486199,   0.97494353,   0.97502507,
       0.97510662,   0.97518816,   0.97526970,   0.97535124,   0.97543278,
       0.97551433,   0.97559587,   0.97567741,   0.97575895,   0.97584049,
       0.97592204,   0.97600358,   0.97608512,   0.97616666,   0.97624820,
       0.97632975,   0.97641129,   0.97649283,   0.97657437,   0.97665591,
       0.97673746,   0.97681900,   0.97690054,   0.97698208,   0.97706362,
       0.97714516,   0.97722671,   0.97730825,   0.97738979,   0.97747133,
       0.97755287,   0.97763442,   0.97771596,   0.97779750,   0.97787904,
       0.97796058,   0.97804213,   0.97812367,   0.97820521,   0.97828675,
       0.97836829,   0.97844984,   0.97853138,   0.97861292,   0.97869446,
       0.97877600,   0.97885754,   0.97893909,   0.97902063,   0.97910217,
       0.97918371,   0.97926525,   0.97934680,   0.97942834,   0.97950988,
       0.97959142,   0.97967296,   0.97975451,   0.97983605,   0.97991759,
       0.97999913,   0.98005099,   0.98010252,   0.98015406,   0.98020559,
       0.98025713,   0.98030867,   0.98036020,   0.98041174,   0.98046327,
       0.98051481,   0.98056634,   0.98061788,   0.98066941,   0.98072095,
       0.98077249,   0.98082402,   0.98087556,   0.98092709,   0.98097863,
       0.98103016,   0.98108170,   0.98113324,   0.98118477,   0.98123631,
       0.98128784,   0.98133938,   0.98139091,   0.98144245,   0.98149399,
       0.98154552,   0.98159706,   0.98164859,   0.98170013,   0.98175166,
       0.98180320,   0.98185474,   0.98190627,   0.98195781,   0.98200934,
       0.98206088,   0.98211241,   0.98216395,   0.98221549,   0.98226702,
       0.98231856,   0.98237009,   0.98242163,   0.98247316,   0.98252470,
       0.98257623,   0.98262777,   0.98267931,   0.98273084,   0.98278238,
       0.98283391,   0.98288545,   0.98293698,   0.98298852,   0.98304006,
       0.98309159,   0.98314313,   0.98319466,   0.98324620,   0.98329773,
       0.98334927,   0.98340081,   0.98345234,   0.98350388,   0.98355541,
       0.98360695,   0.98365848,   0.98371002,   0.98376156,   0.98381309,
       0.98386463,   0.98391616,   0.98396770,   0.98401923,   0.98407077,
       0.98412231,   0.98417384,   0.98422538,   0.98427691,   0.98432845,
       0.98437998,   0.98443152,   0.98448306,   0.98453459,   0.98458613,
       0.98463766,   0.98468920,   0.98474073,   0.98479227,   0.98484380,
       0.98489534,   0.98494688,   0.98499841,   0.98504995,   0.98510148,
       0.98515302,   0.98520455,   0.98525609,   0.98530763,   0.98535916,
       0.98541070,   0.98546223,   0.98551377,   0.98556530,   0.98561684,
       0.98566838,   0.98571991,   0.98577145,   0.98582298,   0.98587452,
       0.98592605,   0.98597759,   0.98602913,   0.98608066,   0.98613220,
       0.98618373,   0.98623527,   0.98628680,   0.98633834,   0.98638988,
       0.98644141,   0.98649295,   0.98654448,   0.98659602,   0.98664755,
       0.98669909,   0.98675063,   0.98680216,   0.98685370,   0.98690523,
       0.98695677,   0.98700830,   0.98705984,   0.98711137,   0.98716291,
       0.98721445,   0.98726598,   0.98731752,   0.98736905,   0.98742059,
       0.98747212,   0.98752366,   0.98757520,   0.98762673,   0.98767827,
       0.98772980,   0.98778134,   0.98783287,   0.98788441,   0.98793595,
       0.98798748,   0.98803902,   0.98809055,   0.98814209,   0.98819362,
       0.98824516,   0.98829670,   0.98834823,   0.98839977,   0.98845130,
       0.98850284,   0.98855437,   0.98860591,   0.98865745,   0.98870898,
       0.98876052,   0.98881205,   0.98886359,   0.98891512,   0.98896666,
       0.98901820,   0.98906973,   0.98912127,   0.98917280,   0.98922434,
       0.98927587,   0.98932741,   0.98937894,   0.98943048,   0.98948202,
       0.98953355,   0.98958509,   0.98963662,   0.98968816,   0.98973969,
       0.98979123,   0.98984277,   0.98989430,   0.98994584,   0.98999737,
       0.99001335,   0.99002741,   0.99004148,   0.99005555,   0.99006961,
       0.99008368,   0.99009774,   0.99011181,   0.99012587,   0.99013994,
       0.99015401,   0.99016807,   0.99018214,   0.99019620,   0.99021027,
       0.99022433,   0.99023840,   0.99025247,   0.99026653,   0.99028060,
       0.99029466,   0.99030873,   0.99032279,   0.99033686,   0.99035093,
       0.99036499,   0.99037906,   0.99039312,   0.99040719,   0.99042125,
       0.99043532,   0.99044939,   0.99046345,   0.99047752,   0.99049158,
       0.99050565,   0.99051971,   0.99053378,   0.99054785,   0.99056191,
       0.99057598,   0.99059004,   0.99060411,   0.99061817,   0.99063224,
       0.99064631,   0.99066037,   0.99067444,   0.99068850,   0.99070257,
       0.99071663,   0.99073070,   0.99074477,   0.99075883,   0.99077290,
       0.99078696,   0.99080103,   0.99081509,   0.99082916,   0.99084323,
       0.99085729,   0.99087136,   0.99088542,   0.99089949,   0.99091355,
       0.99092762,   0.99094169,   0.99095575,   0.99096982,   0.99098388,
       0.99099795,   0.99101201,   0.99102608,   0.99104015,   0.99105421,
       0.99106828,   0.99108234,   0.99109641,   0.99111047,   0.99112454,
       0.99113861,   0.99115267,   0.99116674,   0.99118080,   0.99119487,
       0.99120893,   0.99122300,   0.99123707,   0.99125113,   0.99126520,
       0.99127926,   0.99129333,   0.99130739,   0.99132146,   0.99133553,
       0.99134959,   0.99136366,   0.99137772,   0.99139179,   0.99140585,
       0.99141992,   0.99143399,   0.99144805,   0.99146212,   0.99147618,
       0.99149025,   0.99150431,   0.99151838,   0.99153244,   0.99154651,
       0.99156058,   0.99157464,   0.99158871,   0.99160277,   0.99161684,
       0.99163090,   0.99164497,   0.99165904,   0.99167310,   0.99168717,
       0.99170123,   0.99171530,   0.99172936,   0.99174343,   0.99175750,
       0.99177156,   0.99178563,   0.99179969,   0.99181376,   0.99182782,
       0.99184189,   0.99185596,   0.99187002,   0.99188409,   0.99189815,
       0.99191222,   0.99192628,   0.99194035,   0.99195442,   0.99196848,
       0.99198255,   0.99199661,   0.99201068,   0.99202474,   0.99203881,
       0.99205288,   0.99206694,   0.99208101,   0.99209507,   0.99210914,
       0.99212320,   0.99213727,   0.99215134,   0.99216540,   0.99217947,
       0.99219353,   0.99220760,   0.99222166,   0.99223573,   0.99224980,
       0.99226386,   0.99227793,   0.99229199,   0.99230606,   0.99232012,
       0.99233419,   0.99234826,   0.99236232,   0.99237639,   0.99239045,
       0.99240452,   0.99241858,   0.99243265,   0.99244672,   0.99246078,
       0.99247485,   0.99248891,   0.99250298,   0.99251704,   0.99253111,
       0.99254518,   0.99255924,   0.99257331,   0.99258737,   0.99260144,
       0.99261550,   0.99262957,   0.99264364,   0.99265770,   0.99267177,
       0.99268583,   0.99269990,   0.99271396,   0.99272803,   0.99274210,
       0.99275616,   0.99277023,   0.99278429,   0.99279836,   0.99281242,
       0.99282649,   0.99284056,   0.99285462,   0.99286869,   0.99288275,
       0.99289682,   0.99291088,   0.99292495,   0.99293902,   0.99295308,
       0.99296715,   0.99298121,   0.99299528,   0.99300934,   0.99302341,
       0.99303748,   0.99305154,   0.99306561,   0.99307967,   0.99309374,
       0.99310780,   0.99312187,   0.99313594,   0.99315000,   0.99316407,
       0.99317813,   0.99319220,   0.99320626,   0.99322033,   0.99323440,
       0.99324846,   0.99326253,   0.99327659,   0.99329066,   0.99330472,
       0.99331879,   0.99333286,   0.99334692,   0.99336099,   0.99337505,
       0.99338912,   0.99340318,   0.99341725,   0.99343132,   0.99344538,
       0.99345945,   0.99347351,   0.99348758,   0.99350164,   0.99351571,
       0.99352978,   0.99354384,   0.99355791,   0.99357197,   0.99358604,
       0.99360010,   0.99361417,   0.99362824,   0.99364230,   0.99365637,
       0.99367043,   0.99368450,   0.99369856,   0.99371263,   0.99372670,
       0.99374076,   0.99375483,   0.99376889,   0.99378296,   0.99379702,
       0.99381109,   0.99382516,   0.99383922,   0.99385329,   0.99386735,
       0.99388142,   0.99389548,   0.99390955,   0.99392361,   0.99393768,
       0.99395175,   0.99396581,   0.99397988,   0.99399394,   0.99400801,
       0.99402207,   0.99403614,   0.99405021,   0.99406427,   0.99407834,
       0.99409240,   0.99410647,   0.99412053,   0.99413460,   0.99414867,
       0.99416273,   0.99417680,   0.99419086,   0.99420493,   0.99421899,
       0.99423306,   0.99424713,   0.99426119,   0.99427526,   0.99428932,
       0.99430339,   0.99431745,   0.99433152,   0.99434559,   0.99435965,
       0.99437372,   0.99438778,   0.99440185,   0.99441591,   0.99442998,
       0.99444405,   0.99445811,   0.99447218,   0.99448624,   0.99450031,
       0.99451437,   0.99452844,   0.99454251,   0.99455657,   0.99457064,
       0.99458470,   0.99459877,   0.99461283,   0.99462690,   0.99464097,
       0.99465503,   0.99466910,   0.99468316,   0.99469723,   0.99471129,
       0.99472536,   0.99473943,   0.99475349,   0.99476756,   0.99478162,
       0.99479569,   0.99480975,   0.99482382,   0.99483789,   0.99485195,
       0.99486602,   0.99488008,   0.99489415,   0.99490821,   0.99492228,
       0.99493635,   0.99495041,   0.99496448,   0.99497854,   0.99499261,
       0.99500667,   0.99502074,   0.99503481,   0.99504887,   0.99506294,
       0.99507700,   0.99509107,   0.99510513,   0.99511920,   0.99513327,
       0.99514733,   0.99516140,   0.99517546,   0.99518953,   0.99520359,
       0.99521766,   0.99523173,   0.99524579,   0.99525986,   0.99527392,
       0.99528799,   0.99530205,   0.99531612,   0.99533019,   0.99534425,
       0.99535832,   0.99537238,   0.99538645,   0.99540051,   0.99541458,
       0.99542865,   0.99544271,   0.99545678,   0.99547084,   0.99548491,
       0.99549897,   0.99551304,   0.99552711,   0.99554117,   0.99555524,
       0.99556930,   0.99558337,   0.99559743,   0.99561150,   0.99562557,
       0.99563963,   0.99565370,   0.99566776,   0.99568183,   0.99569589,
       0.99570996,   0.99572403,   0.99573809,   0.99575216,   0.99576622,
       0.99578029,   0.99579435,   0.99580842,   0.99582249,   0.99583655,
       0.99585062,   0.99586468,   0.99587875,   0.99589281,   0.99590688,
       0.99592095,   0.99593501,   0.99594908,   0.99596314,   0.99597721,
       0.99599127,   0.99600534,   0.99601941,   0.99603347,   0.99604754,
       0.99606160,   0.99607567,   0.99608973,   0.99610380,   0.99611787,
       0.99613193,   0.99614600,   0.99616006,   0.99617413,   0.99618819,
       0.99620226,   0.99621633,   0.99623039,   0.99624446,   0.99625852,
       0.99627259,   0.99628665,   0.99630072,   0.99631479,   0.99632885,
       0.99634292,   0.99635698,   0.99637105,   0.99638511,   0.99639918,
       0.99641324,   0.99642731,   0.99644138,   0.99645544,   0.99646951,
       0.99648357,   0.99649764,   0.99651170,   0.99652577,   0.99653984,
       0.99655390,   0.99656797,   0.99658203,   0.99659610,   0.99661016,
       0.99662423,   0.99663830,   0.99665236,   0.99666643,   0.99668049,
       0.99669456,   0.99670862,   0.99672269,   0.99673676,   0.99675082,
       0.99676489,   0.99677895,   0.99679302,   0.99680708,   0.99682115,
       0.99683522,   0.99684928,   0.99686335,   0.99687741,   0.99689148,
       0.99690554,   0.99691961,   0.99693368,   0.99694774,   0.99696181,
       0.99697587,   0.99698994,   0.99700400,   0.99701807,   0.99703214,
       0.99704620,   0.99706027,   0.99707433,   0.99708840,   0.99710246,
       0.99711653,   0.99713060,   0.99714466,   0.99715873,   0.99717279,
       0.99718686,   0.99720092,   0.99721499,   0.99722906,   0.99724312,
       0.99725719,   0.99727125,   0.99728532,   0.99729938,   0.99731345,
       0.99732752,   0.99734158,   0.99735565,   0.99736971,   0.99738378,
       0.99739784,   0.99741191,   0.99742598,   0.99744004,   0.99745411,
       0.99746817,   0.99748224,   0.99749630,   0.99751037,   0.99752444,
       0.99753850,   0.99755257,   0.99756663,   0.99758070,   0.99759476,
       0.99760883,   0.99762290,   0.99763696,   0.99765103,   0.99766509,
       0.99767916,   0.99769322,   0.99770729,   0.99772136,   0.99773542,
       0.99774949,   0.99776355,   0.99777762,   0.99779168,   0.99780575,
       0.99781982,   0.99783388,   0.99784795,   0.99786201,   0.99787608,
       0.99789014,   0.99790421,   0.99791828,   0.99793234,   0.99794641,
       0.99796047,   0.99797454,   0.99798860,   0.99800267,   0.99801674,
       0.99803080,   0.99804487,   0.99805893,   0.99807300,   0.99808706,
       0.99810113,   0.99811520,   0.99812926,   0.99814333,   0.99815739,
       0.99817146,   0.99818552,   0.99819959,   0.99821366,   0.99822772,
       0.99824179,   0.99825585,   0.99826992,   0.99828398,   0.99829805,
       0.99831212,   0.99832618,   0.99834025,   0.99835431,   0.99836838,
       0.99838244,   0.99839651,   0.99841058,   0.99842464,   0.99843871,
       0.99845277,   0.99846684,   0.99848090,   0.99849497,   0.99850904,
       0.99852310,   0.99853717,   0.99855123,   0.99856530,   0.99857936,
       0.99859343,   0.99860750,   0.99862156,   0.99863563,   0.99864969,
       0.99866376,   0.99867782,   0.99869189,   0.99870596,   0.99872002,
       0.99873409,   0.99874815,   0.99876222,   0.99877628,   0.99879035,
       0.99880441,   0.99881848,   0.99883255,   0.99884661,   0.99886068,
       0.99887474,   0.99888881,   0.99890287,   0.99891694,   0.99893101,
       0.99894507,   0.99895914,   0.99897320,   0.99898727,   0.99900133,
       0.99901540,   0.99902947,   0.99904353,   0.99905760,   0.99907166,
       0.99908573,   0.99909979,   0.99911386,   0.99912793,   0.99914199,
       0.99915606,   0.99917012,   0.99918419,   0.99919825,   0.99921232,
       0.99922639,   0.99924045,   0.99925452,   0.99926858,   0.99928265,
       0.99929671,   0.99931078,   0.99932485,   0.99933891,   0.99935298,
       0.99936704,   0.99938111,   0.99939517,   0.99940924,   0.99942331,
       0.99943737,   0.99945144,   0.99946550,   0.99947957,   0.99949363,
       0.99950770,   0.99952177,   0.99953583,   0.99954990,   0.99956396,
       0.99957803,   0.99959209,   0.99960616,   0.99962023,   0.99963429,
       0.99964836,   0.99966242,   0.99967649,   0.99969055,   0.99970462,
       0.99971869,   0.99973275,   0.99974682,   0.99976088,   0.99977495,
       0.99978901,   0.99980308,   0.99981715,   0.99983121,   0.99984528,
       0.99985934,   0.99987341,   0.99988747,   0.99990154,   0.99991561,
       0.99992967,   0.99994374,   0.99995780,   0.99997187,   0.99998593,
       1.00000000 };

                     int i = (int)ceil( x * (2000));
       return alpha1_3[i];
}

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <stdexcept>
#include <chrono>
#include <vector>

/*
--- Day 3: Mull It Over ---
"Our computers are having issues, so I have no idea if we have any Chief Historians in stock! 
You're welcome to check the warehouse, though," 
says the mildly flustered shopkeeper at the North Pole Toboggan Rental Shop. 
The Historians head out to take a look.

The shopkeeper turns to you. 
"Any chance you can see why our computers are having issues again?"

The computer appears to be trying to run a program, 
but its memory (your puzzle input) is corrupted. 
All of the instructions have been jumbled up!

It seems like the goal of the program is just to multiply some numbers. 
It does that with instructions like mul(X,Y), 
where X and Y are each 1-3 digit numbers. 
For instance, mul(44,46) multiplies 44 by 46 to get a result of 2024. 
Similarly, mul(123,4) would multiply 123 by 4.

However, because the program's memory has been corrupted, 
there are also many invalid characters that should be ignored, 
even if they look like part of a mul instruction. 
Sequences like mul(4*, mul(6,9!, ?(12,34), or mul ( 2 , 4 ) do nothing.

For example, consider the following section of corrupted memory:
xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))

Only the four highlighted sections are real mul instructions. 
Adding up the result of each instruction produces 161 (2*4 + 5*5 + 11*8 + 8*5).

Scan the corrupted memory for uncorrupted mul instructions. 
What do you get if you add up all of the results of the multiplications?

--- Part Two ---
As you scan through the corrupted memory, 
you notice that some of the conditional statements are also still intact. 
If you handle some of the uncorrupted conditional statements in the program, 
you might be able to get an even more accurate result.

There are two new instructions you'll need to handle:

The do() instruction enables future mul instructions.
The don't() instruction disables future mul instructions.
Only the most recent do() or don't() instruction applies. 
At the beginning of the program, mul instructions are enabled.


For example:
xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))

This corrupted memory is similar to the example from before, 
but this time the mul(5,5) and mul(11,8) instructions are disabled because there is a don't() instruction before them. 
The other mul instructions function normally, 
including the one at the end that gets re-enabled by a do() instruction.

This time, the sum of the results is 48 (2*4 + 8*5).

Handle the new instructions; 
what do you get if you add up all of the results of just the enabled multiplications?

*/

#define SAMPLE 1

#ifdef SAMPLE
    #define FILENAME "sample2.txt"
    std::string s_test = "xmul(2,4)&mul[3,7]!^?mul(8,5))";    
    //std::string s_test = "}mul(417,770)%why(){/':mul(187,313)<@*select()mul(908,713)who()$mul(156,598)#from()* from()^-mul(233,874)&when()mul(346,616)what()(select(),when()where()when()when()&}mul(814,171)+;how() ?)when()?mul(68,188),[select(336,87)^%when(108,692)#mul(621,712){}when()how(69,755)mul(273,27)+:'?( /what()who()from()mul(135,680)-]{:;mul(7,723)where()@{mul(626,107))how()//when(),~+mul(834,113)&!where()$mul(951,76) /why(767,720)mul(107,588)mul(632,977)mul(55,47))[select()']what()mul(803,299)&%#mul(684,214)]}{-}[mul(806,141),mul(166,98)(select()<what():{^mul(98,724)(]from(),what()#,(mul(71,173)from(192,627)&}~when()/mul(142,594)what()<from(594,583)/[~@mul(48,200)why()]^[%/mul(153,486)~:why(),'/mul(555,221): ]+mul(964,152)]/-;why()mul(928,59)+ who(345,334)where()where()mul(953,755))^from()<from()>[*'mul(619,823)mul(633,178)-how()from()?from()*#what()'mul(806,961)what()!?mul(529,544)?+[@$where()mul(498,66)?where()why()who()when()why()'from(742,433)mul(623,31)what()&{>]when()who()$/who()!+^mul(579,603);>mul(365,610)!#<^;mul(802,476)}')select()what()&mul(98,768)^<'~#][{where()<mul(330,387)mul(30,766){who()#from()%&mul(146,838)who()}where();how()+where():mul(593,206)/(>mul(173,805)}what()/$#<why()>#}mul(369,326):why(421,566)#mul(357where(305,979)what()*)*mul(775,55){when()%select()~/what() /mul(332,608)-who(),mul(592,150)~/#&#}]mul(453,71>~'from()~%mul(540,100)$/:}#(@ mul(789,978)%$](#{>]?mul(473,873)when()where() {@]why()mul(606,201)who()how()mul(212,663)^;#:when())#";
    //std::string s_test = "when(578,754)mul(12,923)# /+who();&'^mul(874,174))from()] mul(294+$$[when()where()+mul(118,975)mul(954,230)(+when()mul(579,726)why()$+]$mul(796,252):@ ^?mul(108,275) $)who()why()^mul(782,400);*@~what()'-mul(712,375)[!who(791,378)mul(163,311-]:@!#[select()%%,mul(375,461)*''from()><},@<mul(571,946)) what()!]#{why()mul(638,465) what()$+ +who()mul(446,329)why()how()-where()who()*mul(217,552)how()where()$-^@]mul(29,459)'mul(931,903)-,]?):mul(685,345)}[>{( ;mul(361,764)@mul(71,571)?%~from()what()[ +mul(384,899)@:]mul(627,870select():@!]/mul(676,247)?$what()%who()&from()from(228,681) mul(974@why()*mul(101,691)^[why()how()+&mul(228,575)%$where()&#why()from()mul(601,339)#:>@(from()mul(9,628)~{$],why(412,785)):mul(921,60)?when()$mul(230,472)%where(){?}@{mul(57,287)mul(620,392)who()))how()')}mul(920,110)) how()why()>*)from()'mul(66,955)who()mul(339,162)how()from()#mul(63,609)?+how()<&#where() mul(917,834)(mul(845,751)/mul(803,539)~>&:##?:why()<mul(554,940)from():;where()&who()what(807,73)from()mul(742,258)<why() why(764,736)from()when()who()mul(487,500)(%when()~+/{))[mul(689,792#why()when()>']%<select()-mul(455,937)mul(520,734)select()select()why()@@mul(330,396:,;&?where(511,149))what()<mul(528,808){::why()]['mul(482,123)how()#why()>why()+:@who()[from()]mul(490,50;who()((when()!why()mul(667,140)what()mul]*from()!^}why()}>:~ {(select():why()*mul(691,254)select()why()mul(911,232)where()]#;'";
#else
    #define FILENAME "input.txt"
#endif

std::vector<std::string> DataSet;

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

std::vector<std::string> ExplodeString(std::string input, std::string delimiter = " " ) {
    std::vector<std::string> List;
    size_t pos = 0;
    std::string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        List.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    List.push_back(input); // Add the last token
    return List;
}

void ReadFile( std::string filename ) {
    std::string line;
    std::ifstream myfile;
    myfile.open( filename );
    int Count = 0;

    try
    {
        if (myfile.is_open()){
            while ( getline( myfile, line ) ) {
                DataSet.push_back(line);
            }
        } else throw( std::exception() );
        myfile.close();
    }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n'; }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    ReadFile( FILENAME );

    int count = 0;
    bool enabled = true;

    std::string sDS;
    for( std::string s1 : DataSet ) sDS += s1;

    int pos = 0;
    int do_pos = 0;
    int dont_pos = 0;
    bool run = true;

    while(run){
        dont_pos = sDS.find("don't()");
        if (dont_pos == std::string::npos) {
            run = false;
            break;
        }
        do_pos = sDS.find("do()");
        if (do_pos == std::string::npos){
            sDS = sDS.substr(0,dont_pos);
            break;
        }
        sDS.erase(dont_pos, do_pos-dont_pos+4);
    }

#ifdef SAMPLE
    if(sDS != s_test ){
        throw new std::exception();
    }
#endif

    std::vector<std::string> sDSv = ExplodeString(sDS,"mul(");
    for( std::string s3 : sDSv ){
        int c_pos = s3.find_first_of(',');
        int p_pos = s3.find_first_of(')');
        if(c_pos == std::string::npos | p_pos == std::string::npos ) continue;
        std::string sA = s3.substr(0,c_pos);
        std::string sB = s3.substr(c_pos+1,p_pos-(c_pos+1));
        if( sA.length()>3 | sB.length()>3 ) continue;
        int iA = stoi(sA);
        int iB = stoi(sB);
        int iM = iA * iB;
        count += iM;
        std::cout << "A: " << iA << ", B: " << iB << " M:" << iM << "\n";
    }

    std::cout << "Count: " << count << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
    return 0;
}

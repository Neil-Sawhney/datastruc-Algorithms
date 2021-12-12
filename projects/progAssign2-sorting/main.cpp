// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2021

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData : l) {
    output << pData->lastName << " " << pData->firstName << " " << pData->ssn
           << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.
#include <map>
#include <unordered_map>

const string lastNamesString[500] = {
    "ACOSTA",     "ADAMS",      "ADKINS",     "AGUILAR",     "AGUIRRE",
    "ALEXANDER",  "ALLEN",      "ALVARADO",   "ALVAREZ",     "ANDERSON",
    "ANDREWS",    "ARMSTRONG",  "ARNOLD",     "AUSTIN",      "AVILA",
    "AYALA",      "BAILEY",     "BAKER",      "BALDWIN",     "BANKS",
    "BARBER",     "BARKER",     "BARNES",     "BARNETT",     "BARRETT",
    "BARTON",     "BATES",      "BECK",       "BECKER",      "BELL",
    "BENNETT",    "BENSON",     "BERRY",      "BISHOP",      "BLACK",
    "BLAIR",      "BLAKE",      "BOWEN",      "BOWMAN",      "BOYD",
    "BRADLEY",    "BRADY",      "BREWER",     "BROOKS",      "BROWN",
    "BRYANT",     "BURGESS",    "BURKE",      "BURNS",       "BURTON",
    "BUSH",       "BUTLER",     "BYRD",       "CABRERA",     "CALDERON",
    "CALDWELL",   "CAMACHO",    "CAMPBELL",   "CAMPOS",      "CANNON",
    "CARDENAS",   "CARLSON",    "CARPENTER",  "CARR",        "CARRILLO",
    "CARROLL",    "CARTER",     "CASTANEDA",  "CASTILLO",    "CASTRO",
    "CERVANTES",  "CHAMBERS",   "CHAN",       "CHANDLER",    "CHANG",
    "CHAPMAN",    "CHAVEZ",     "CHEN",       "CHRISTENSEN", "CLARK",
    "CLARKE",     "COHEN",      "COLE",       "COLEMAN",     "COLLINS",
    "COLON",      "CONTRERAS",  "COOK",       "COOPER",      "CORTEZ",
    "COX",        "CRAIG",      "CRAWFORD",   "CROSS",       "CRUZ",
    "CUMMINGS",   "CUNNINGHAM", "CURRY",      "CURTIS",      "DANIEL",
    "DANIELS",    "DAVIDSON",   "DAVIS",      "DAWSON",      "DAY",
    "DEAN",       "DELACRUZ",   "DELEON",     "DELGADO",     "DENNIS",
    "DIAZ",       "DIXON",      "DOMINGUEZ",  "DOUGLAS",     "DOYLE",
    "DUNCAN",     "DUNN",       "DURAN",      "EDWARDS",     "ELLIOTT",
    "ELLIS",      "ERICKSON",   "ESPINOZA",   "ESTRADA",     "EVANS",
    "FARMER",     "FERGUSON",   "FERNANDEZ",  "FIELDS",      "FIGUEROA",
    "FISCHER",    "FISHER",     "FITZGERALD", "FLEMING",     "FLETCHER",
    "FLORES",     "FORD",       "FOSTER",     "FOWLER",      "FOX",
    "FRANCIS",    "FRANCO",     "FRANK",      "FRANKLIN",    "FRAZIER",
    "FREEMAN",    "FUENTES",    "FULLER",     "GALLAGHER",   "GALLEGOS",
    "GARCIA",     "GARDNER",    "GARNER",     "GARRETT",     "GARZA",
    "GEORGE",     "GIBSON",     "GILBERT",    "GILL",        "GOMEZ",
    "GONZALES",   "GONZALEZ",   "GOODMAN",    "GOODWIN",     "GORDON",
    "GRAHAM",     "GRANT",      "GRAVES",     "GRAY",        "GREEN",
    "GREENE",     "GREGORY",    "GRIFFIN",    "GRIFFITH",    "GROSS",
    "GUERRA",     "GUERRERO",   "GUTIERREZ",  "GUZMAN",      "HAIL",
    "HALE",       "HALL",       "HAMILTON",   "HAMMOND",     "HAMPTON",
    "HANSEN",     "HANSON",     "HARDY",      "HARMON",      "HARPER",
    "HARRINGTON", "HARRIS",     "HARRISON",   "HART",        "HARVEY",
    "HAWKINS",    "HAYES",      "HAYNES",     "HENDERSON",   "HENRY",
    "HERNANDEZ",  "HERRERA",    "HICKS",      "HIGGINS",     "HILL",
    "HINES",      "HODGES",     "HOFFMAN",    "HOLLAND",     "HOLMES",
    "HOLT",       "HOPKINS",    "HORTON",     "HOWARD",      "HOWELL",
    "HUANG",      "HUBBARD",    "HUDSON",     "HUGHES",      "HUNT",
    "HUNTER",     "INGRAM",     "JACKSON",    "JACOBS",      "JAMES",
    "JENKINS",    "JENNINGS",   "JENSEN",     "JIMENEZ",     "JOHNSON",
    "JOHNSTON",   "JONES",      "JORDAN",     "JOSEPH",      "JUAREZ",
    "KELLER",     "KELLEY",     "KELLY",      "KENNEDY",     "KHAN",
    "KIM",        "KING",       "KLEIN",      "KNIGHT",      "LAMBERT",
    "LANE",       "LARA",       "LARSON",     "LAWRENCE",    "LAWSON",
    "LE",         "LEE",        "LEON",       "LEONARD",     "LEWIS",
    "LI",         "LIN",        "LITTLE",     "LIU",         "LOGAN",
    "LONG",       "LOPEZ",      "LOVE",       "LOWE",        "LUCAS",
    "LUNA",       "LYNCH",      "LYONS",      "MACK",        "MALDONADO",
    "MALONE",     "MANN",       "MANNING",    "MARQUEZ",     "MARSHALL",
    "MARTIN",     "MARTINEZ",   "MASON",      "MATTHEWS",    "MAXWELL",
    "MAY",        "MCCARTHY",   "MCCOY",      "MCDANIEL",    "MCDONALD",
    "MCGEE",      "MCKINNEY",   "MCLAUGHLIN", "MEDINA",      "MEJIA",
    "MENDEZ",     "MENDOZA",    "MEYER",      "MILES",       "MILLER",
    "MILLS",      "MIRANDA",    "MITCHELL",   "MOLINA",      "MONTGOMERY",
    "MONTOYA",    "MOORE",      "MORALES",    "MORAN",       "MORENO",
    "MORGAN",     "MORRIS",     "MORRISON",   "MOSS",        "MULLINS",
    "MUNOZ",      "MURPHY",     "MURRAY",     "MYERS",       "NAVARRO",
    "NEAL",       "NELSON",     "NEWMAN",     "NEWTON",      "NGUYEN",
    "NICHOLS",    "NORMAN",     "NORRIS",     "NUNEZ",       "OBRIEN",
    "OCHOA",      "OCONNOR",    "OLIVER",     "OLSON",       "ORTEGA",
    "ORTIZ",      "OWENS",      "PACHECO",    "PADILLA",     "PAGE",
    "PALMER",     "PARK",       "PARKER",     "PARKS",       "PARSONS",
    "PATEL",      "PATTERSON",  "PAUL",       "PAYNE",       "PEARSON",
    "PENA",       "PEREZ",      "PERKINS",    "PERRY",       "PERSON",
    "PETERS",     "PETERSON",   "PHAM",       "PHILLIPS",    "PIERCE",
    "PORTER",     "POTTER",     "POWELL",     "POWERS",      "PRICE",
    "QUINN",      "RAMIREZ",    "RAMOS",      "RAMSEY",      "RAY",
    "REED",       "REESE",      "REEVES",     "REID",        "REYES",
    "REYNOLDS",   "RHODES",     "RICE",       "RICHARDS",    "RICHARDSON",
    "RILEY",      "RIOS",       "RIVAS",      "RIVERA",      "ROBBINS",
    "ROBERTS",    "ROBERTSON",  "ROBINSON",   "ROBLES",      "RODGERS",
    "RODRIGUEZ",  "ROGERS",     "ROJAS",      "ROMAN",       "ROMERO",
    "ROSALES",    "ROSE",       "ROSS",       "ROWE",        "RUIZ",
    "RUSSELL",    "RYAN",       "SALAZAR",    "SALINAS",     "SANCHEZ",
    "SANDERS",    "SANDOVAL",   "SANTIAGO",   "SANTOS",      "SAUNDERS",
    "SCHMIDT",    "SCHNEIDER",  "SCHROEDER",  "SCHULTZ",     "SCHWARTZ",
    "SCOTT",      "SERRANO",    "SHARP",      "SHAW",        "SHELTON",
    "SHERMAN",    "SILVA",      "SIMMONS",    "SIMON",       "SIMPSON",
    "SIMS",       "SINGH",      "SMITH",      "SNYDER",      "SOLIS",
    "SOTO",       "SPENCER",    "STANLEY",    "STEELE",      "STEPHENS",
    "STEVENS",    "STEVENSON",  "STEWART",    "STONE",       "STRICKLAND",
    "SULLIVAN",   "SUTTON",     "SWANSON",    "TATE",        "TAYLOR",
    "TERRY",      "THOMAS",     "THOMPSON",   "THORNTON",    "TODD",
    "TORRES",     "TOWNSEND",   "TRAN",       "TRUJILLO",    "TUCKER",
    "TURNER",     "VALDEZ",     "VALENCIA",   "VARGAS",      "VASQUEZ",
    "VAUGHN",     "VAZQUEZ",    "VEGA",       "VELASQUEZ",   "WADE",
    "WAGNER",     "WALKER",     "WALLACE",    "WALSH",       "WALTERS",
    "WALTON",     "WANG",       "WARD",       "WARNER",      "WARREN",
    "WASHINGTON", "WATERS",     "WATKINS",    "WATSON",      "WATTS",
    "WEAVER",     "WEBB",       "WEBER",      "WEBSTER",     "WELCH",
    "WELLS",      "WEST",       "WHEELER",    "WHITE",       "WILLIAMS",
    "WILLIAMSON", "WILLIS",     "WILSON",     "WISE",        "WOLF",
    "WOLFE",      "WONG",       "WOOD",       "WOODS",       "WRIGHT",
    "WU",         "YANG",       "YOUNG",      "ZHANG",       "ZIMMERMAN"};

const string firstNamesString[500] = {
    "AALIYAH",   "AARON",     "ABEL",      "ABIGAIL",   "ABRAHAM",
    "ADALINE",   "ADALYN",    "ADALYNN",   "ADAM",      "ADDISON",
    "ADELINE",   "ADELYN",    "ADRIAN",    "ADRIANA",   "AIDAN",
    "AIDEN",     "ALAINA",    "ALAN",      "ALANA",     "ALAYNA",
    "ALEJANDRO", "ALEX",      "ALEXA",     "ALEXANDER", "ALEXANDRA",
    "ALEXIS",    "ALICE",     "ALINA",     "ALIVIA",    "ALIYAH",
    "ALLISON",   "ALYSSA",    "AMARA",     "AMAYA",     "AMELIA",
    "AMIR",      "AMY",       "ANA",       "ANASTASIA", "ANDREA",
    "ANDRES",    "ANDREW",    "ANGEL",     "ANGELA",    "ANGELINA",
    "ANNA",      "ANNABELLE", "ANTHONY",   "ANTONIO",   "ARABELLA",
    "ARIA",      "ARIANA",    "ARIANNA",   "ARIEL",     "ARTHUR",
    "ARYA",      "ASHER",     "ASHLEY",    "ASHTON",    "ATHENA",
    "AUBREE",    "AUBREY",    "AUDREY",    "AUGUST",    "AURORA",
    "AUSTIN",    "AUTUMN",    "AVA",       "AVERY",     "AXEL",
    "AYDEN",     "AYLA",      "BAILEY",    "BARRETT",   "BEAU",
    "BECKETT",   "BELLA",     "BENJAMIN",  "BENNETT",   "BENTLEY",
    "BLAKE",     "BRADLEY",   "BRADY",     "BRANDON",   "BRANTLEY",
    "BRAXTON",   "BRAYDEN",   "BRIAN",     "BRIANNA",   "BRIELLE",
    "BRODY",     "BROOKE",    "BROOKLYN",  "BROOKLYNN", "BROOKS",
    "BRYAN",     "BRYCE",     "BRYNLEE",   "BRYSON",    "CADEN",
    "CALEB",     "CALLIE",    "CALVIN",    "CAMDEN",    "CAMERON",
    "CAMILA",    "CARLOS",    "CAROLINE",  "CARSON",    "CARTER",
    "CATHERINE", "CAYDEN",    "CECILIA",   "CHARLES",   "CHARLIE",
    "CHARLOTTE", "CHASE",     "CHLOE",     "CHRISTIAN", "CHRISTOPHER",
    "CLAIRE",    "CLARA",     "CLAYTON",   "COLE",      "COLIN",
    "COLTON",    "CONNOR",    "COOPER",    "CORA",      "DAISY",
    "DAKOTA",    "DALEYZA",   "DAMIAN",    "DANIEL",    "DANIELA",
    "DAVID",     "DAWSON",    "DEAN",      "DECLAN",    "DELANEY",
    "DELILAH",   "DEREK",     "DESTINY",   "DIANA",     "DIEGO",
    "DOMINIC",   "DYLAN",     "EASTON",    "EDEN",      "EDWARD",
    "ELEANOR",   "ELENA",     "ELI",       "ELIANA",    "ELIAS",
    "ELIJAH",    "ELISE",     "ELIZA",     "ELIZABETH", "ELLA",
    "ELLIANA",   "ELLIE",     "ELLIOT",    "ELLIOTT",   "ELOISE",
    "EMERSON",   "EMERSYN",   "EMERY",     "EMILIA",    "EMILIANO",
    "EMILY",     "EMMA",      "EMMANUEL",  "EMMETT",    "ERIC",
    "ESTHER",    "ETHAN",     "EVA",       "EVAN",      "EVELYN",
    "EVERETT",   "EVERLY",    "EZEKIEL",   "EZRA",      "FAITH",
    "FELIX",     "FINLEY",    "FINN",      "FIONA",     "GABRIEL",
    "GABRIELLA", "GAEL",      "GAVIN",     "GENESIS",   "GENEVIEVE",
    "GEORGE",    "GEORGIA",   "GIANNA",    "GIOVANNI",  "GRACE",
    "GRACIE",    "GRAHAM",    "GRANT",     "GRAYSON",   "GREYSON",
    "GRIFFIN",   "HADLEY",    "HAILEY",    "HANNAH",    "HARLEY",
    "HARMONY",   "HARPER",    "HARRISON",  "HAYDEN",    "HAZEL",
    "HENRY",     "HOLDEN",    "HUDSON",    "HUNTER",    "IAN",
    "IRIS",      "ISAAC",     "ISABEL",    "ISABELLA",  "ISABELLE",
    "ISAIAH",    "ISLA",      "ISRAEL",    "IVAN",      "IVY",
    "JACE",      "JACK",      "JACKSON",   "JACOB",     "JADE",
    "JADEN",     "JAKE",      "JAMES",     "JAMESON",   "JASMINE",
    "JASON",     "JASPER",    "JAVIER",    "JAX",       "JAXON",
    "JAXSON",    "JAYCE",     "JAYDEN",    "JAYLA",     "JEREMIAH",
    "JEREMY",    "JESSE",     "JESSICA",   "JESUS",     "JOANNA",
    "JOCELYN",   "JOEL",      "JOHN",      "JONAH",     "JONATHAN",
    "JORDAN",    "JORDYN",    "JORGE",     "JOSE",      "JOSEPH",
    "JOSEPHINE", "JOSHUA",    "JOSIAH",    "JOSIE",     "JOSUE",
    "JUAN",      "JUDAH",     "JUDE",      "JULIA",     "JULIAN",
    "JULIANA",   "JULIANNA",  "JULIET",    "JULIETTE",  "JUNE",
    "JUSTIN",    "KADEN",     "KAI",       "KAIDEN",    "KALEB",
    "KARTER",    "KATHERINE", "KAYDEN",    "KAYLA",     "KAYLEE",
    "KENDALL",   "KENNEDY",   "KENNETH",   "KEVIN",     "KHLOE",
    "KILLIAN",   "KIMBERLY",  "KING",      "KINGSTON",  "KINSLEY",
    "KNOX",      "KYLE",      "KYLIE",     "KYRIE",     "LAILA",
    "LANDON",    "LAUREN",    "LAYLA",     "LEAH",      "LEILA",
    "LEILANI",   "LEO",       "LEON",      "LEONARDO",  "LEVI",
    "LIAM",      "LILA",      "LILIANA",   "LILLIAN",   "LILLY",
    "LILY",      "LINCOLN",   "LOGAN",     "LOLA",      "LONDON",
    "LONDYN",    "LORENZO",   "LUCA",      "LUCAS",     "LUCIA",
    "LUCY",      "LUIS",      "LUKAS",     "LUKE",      "LUNA",
    "LYDIA",     "LYLA",      "MACKENZIE", "MADDOX",    "MADELINE",
    "MADELYN",   "MADISON",   "MAGGIE",    "MAKAYLA",   "MALACHI",
    "MALIA",     "MARCUS",    "MARGARET",  "MARIA",     "MARIAH",
    "MARK",      "MARLEY",    "MARY",      "MASON",     "MATEO",
    "MATIAS",    "MATTEO",    "MATTHEW",   "MAVERICK",  "MAX",
    "MAXIMUS",   "MAXWELL",   "MAYA",      "MCKENZIE",  "MELANIE",
    "MELODY",    "MESSIAH",   "MIA",       "MICAH",     "MICHAEL",
    "MICHELLE",  "MIGUEL",    "MILA",      "MILES",     "MILO",
    "MOLLY",     "MORGAN",    "MYA",       "MYLES",     "NAOMI",
    "NATALIA",   "NATALIE",   "NATHAN",    "NATHANIEL", "NEVAEH",
    "NICHOLAS",  "NICOLAS",   "NICOLE",    "NOAH",      "NOELLE",
    "NOLAN",     "NORA",      "NORAH",     "NOVA",      "OLIVER",
    "OLIVIA",    "OMAR",      "OSCAR",     "OWEN",      "PAIGE",
    "PAISLEY",   "PARKER",    "PATRICK",   "PAUL",      "PAXTON",
    "PAYTON",    "PENELOPE",  "PETER",     "PEYTON",    "PIPER",
    "PRESLEY",   "PRESTON",   "QUINN",     "RACHEL",    "RAELYNN",
    "REAGAN",    "REBECCA",   "REESE",     "REMI",      "REMINGTON",
    "RHETT",     "RICHARD",   "RILEY",     "RIVER",     "ROBERT",
    "ROMAN",     "ROSALIE",   "ROSE",      "ROWAN",     "RUBY",
    "RYAN",      "RYDER",     "RYKER",     "RYLEE",     "RYLEIGH",
    "SADIE",     "SAMANTHA",  "SAMUEL",    "SANTIAGO",  "SARA",
    "SARAH",     "SAVANNAH",  "SAWYER",    "SCARLETT",  "SEBASTIAN",
    "SELENA",    "SERENITY",  "SIENNA",    "SILAS",     "SKYLAR",
    "SLOANE",    "SOFIA",     "SOPHIA",    "SOPHIE",    "STELLA",
    "STEVEN",    "SUMMER",    "SYDNEY",    "TAYLOR",    "TEAGAN",
    "TESSA",     "THEODORE",  "THIAGO",    "THOMAS",    "TIMOTHY",
    "TRINITY",   "TRISTAN",   "TUCKER",    "TYLER",     "VALENTINA",
    "VALERIA",   "VALERIE",   "VANESSA",   "VICTOR",    "VICTORIA",
    "VINCENT",   "VIOLET",    "VIVIAN",    "WAYLON",    "WESLEY",
    "WESTON",    "WILLIAM",   "WILLOW",    "WYATT",     "XANDER",
    "XAVIER",    "XIMENA",    "ZACHARY",   "ZANDER",    "ZANE",
    "ZAYDEN",    "ZION",      "ZOE",       "ZOEY"};

unordered_map<string, vector<Data *>> firstNamesNumberedMap = {
    {"AALIYAH", vector<Data *>()},   {"AARON", vector<Data *>()},
    {"ABEL", vector<Data *>()},      {"ABIGAIL", vector<Data *>()},
    {"ABRAHAM", vector<Data *>()},   {"ADALINE", vector<Data *>()},
    {"ADALYN", vector<Data *>()},    {"ADALYNN", vector<Data *>()},
    {"ADAM", vector<Data *>()},      {"ADDISON", vector<Data *>()},
    {"ADELINE", vector<Data *>()},   {"ADELYN", vector<Data *>()},
    {"ADRIAN", vector<Data *>()},    {"ADRIANA", vector<Data *>()},
    {"AIDAN", vector<Data *>()},     {"AIDEN", vector<Data *>()},
    {"ALAINA", vector<Data *>()},    {"ALAN", vector<Data *>()},
    {"ALANA", vector<Data *>()},     {"ALAYNA", vector<Data *>()},
    {"ALEJANDRO", vector<Data *>()}, {"ALEX", vector<Data *>()},
    {"ALEXA", vector<Data *>()},     {"ALEXANDER", vector<Data *>()},
    {"ALEXANDRA", vector<Data *>()}, {"ALEXIS", vector<Data *>()},
    {"ALICE", vector<Data *>()},     {"ALINA", vector<Data *>()},
    {"ALIVIA", vector<Data *>()},    {"ALIYAH", vector<Data *>()},
    {"ALLISON", vector<Data *>()},   {"ALYSSA", vector<Data *>()},
    {"AMARA", vector<Data *>()},     {"AMAYA", vector<Data *>()},
    {"AMELIA", vector<Data *>()},    {"AMIR", vector<Data *>()},
    {"AMY", vector<Data *>()},       {"ANA", vector<Data *>()},
    {"ANASTASIA", vector<Data *>()}, {"ANDREA", vector<Data *>()},
    {"ANDRES", vector<Data *>()},    {"ANDREW", vector<Data *>()},
    {"ANGEL", vector<Data *>()},     {"ANGELA", vector<Data *>()},
    {"ANGELINA", vector<Data *>()},  {"ANNA", vector<Data *>()},
    {"ANNABELLE", vector<Data *>()}, {"ANTHONY", vector<Data *>()},
    {"ANTONIO", vector<Data *>()},   {"ARABELLA", vector<Data *>()},
    {"ARIA", vector<Data *>()},      {"ARIANA", vector<Data *>()},
    {"ARIANNA", vector<Data *>()},   {"ARIEL", vector<Data *>()},
    {"ARTHUR", vector<Data *>()},    {"ARYA", vector<Data *>()},
    {"ASHER", vector<Data *>()},     {"ASHLEY", vector<Data *>()},
    {"ASHTON", vector<Data *>()},    {"ATHENA", vector<Data *>()},
    {"AUBREE", vector<Data *>()},    {"AUBREY", vector<Data *>()},
    {"AUDREY", vector<Data *>()},    {"AUGUST", vector<Data *>()},
    {"AURORA", vector<Data *>()},    {"AUSTIN", vector<Data *>()},
    {"AUTUMN", vector<Data *>()},    {"AVA", vector<Data *>()},
    {"AVERY", vector<Data *>()},     {"AXEL", vector<Data *>()},
    {"AYDEN", vector<Data *>()},     {"AYLA", vector<Data *>()},
    {"BAILEY", vector<Data *>()},    {"BARRETT", vector<Data *>()},
    {"BEAU", vector<Data *>()},      {"BECKETT", vector<Data *>()},
    {"BELLA", vector<Data *>()},     {"BENJAMIN", vector<Data *>()},
    {"BENNETT", vector<Data *>()},   {"BENTLEY", vector<Data *>()},
    {"BLAKE", vector<Data *>()},     {"BRADLEY", vector<Data *>()},
    {"BRADY", vector<Data *>()},     {"BRANDON", vector<Data *>()},
    {"BRANTLEY", vector<Data *>()},  {"BRAXTON", vector<Data *>()},
    {"BRAYDEN", vector<Data *>()},   {"BRIAN", vector<Data *>()},
    {"BRIANNA", vector<Data *>()},   {"BRIELLE", vector<Data *>()},
    {"BRODY", vector<Data *>()},     {"BROOKE", vector<Data *>()},
    {"BROOKLYN", vector<Data *>()},  {"BROOKLYNN", vector<Data *>()},
    {"BROOKS", vector<Data *>()},    {"BRYAN", vector<Data *>()},
    {"BRYCE", vector<Data *>()},     {"BRYNLEE", vector<Data *>()},
    {"BRYSON", vector<Data *>()},    {"CADEN", vector<Data *>()},
    {"CALEB", vector<Data *>()},     {"CALLIE", vector<Data *>()},
    {"CALVIN", vector<Data *>()},    {"CAMDEN", vector<Data *>()},
    {"CAMERON", vector<Data *>()},   {"CAMILA", vector<Data *>()},
    {"CARLOS", vector<Data *>()},    {"CAROLINE", vector<Data *>()},
    {"CARSON", vector<Data *>()},    {"CARTER", vector<Data *>()},
    {"CATHERINE", vector<Data *>()}, {"CAYDEN", vector<Data *>()},
    {"CECILIA", vector<Data *>()},   {"CHARLES", vector<Data *>()},
    {"CHARLIE", vector<Data *>()},   {"CHARLOTTE", vector<Data *>()},
    {"CHASE", vector<Data *>()},     {"CHLOE", vector<Data *>()},
    {"CHRISTIAN", vector<Data *>()}, {"CHRISTOPHER", vector<Data *>()},
    {"CLAIRE", vector<Data *>()},    {"CLARA", vector<Data *>()},
    {"CLAYTON", vector<Data *>()},   {"COLE", vector<Data *>()},
    {"COLIN", vector<Data *>()},     {"COLTON", vector<Data *>()},
    {"CONNOR", vector<Data *>()},    {"COOPER", vector<Data *>()},
    {"CORA", vector<Data *>()},      {"DAISY", vector<Data *>()},
    {"DAKOTA", vector<Data *>()},    {"DALEYZA", vector<Data *>()},
    {"DAMIAN", vector<Data *>()},    {"DANIEL", vector<Data *>()},
    {"DANIELA", vector<Data *>()},   {"DAVID", vector<Data *>()},
    {"DAWSON", vector<Data *>()},    {"DEAN", vector<Data *>()},
    {"DECLAN", vector<Data *>()},    {"DELANEY", vector<Data *>()},
    {"DELILAH", vector<Data *>()},   {"DEREK", vector<Data *>()},
    {"DESTINY", vector<Data *>()},   {"DIANA", vector<Data *>()},
    {"DIEGO", vector<Data *>()},     {"DOMINIC", vector<Data *>()},
    {"DYLAN", vector<Data *>()},     {"EASTON", vector<Data *>()},
    {"EDEN", vector<Data *>()},      {"EDWARD", vector<Data *>()},
    {"ELEANOR", vector<Data *>()},   {"ELENA", vector<Data *>()},
    {"ELI", vector<Data *>()},       {"ELIANA", vector<Data *>()},
    {"ELIAS", vector<Data *>()},     {"ELIJAH", vector<Data *>()},
    {"ELISE", vector<Data *>()},     {"ELIZA", vector<Data *>()},
    {"ELIZABETH", vector<Data *>()}, {"ELLA", vector<Data *>()},
    {"ELLIANA", vector<Data *>()},   {"ELLIE", vector<Data *>()},
    {"ELLIOT", vector<Data *>()},    {"ELLIOTT", vector<Data *>()},
    {"ELOISE", vector<Data *>()},    {"EMERSON", vector<Data *>()},
    {"EMERSYN", vector<Data *>()},   {"EMERY", vector<Data *>()},
    {"EMILIA", vector<Data *>()},    {"EMILIANO", vector<Data *>()},
    {"EMILY", vector<Data *>()},     {"EMMA", vector<Data *>()},
    {"EMMANUEL", vector<Data *>()},  {"EMMETT", vector<Data *>()},
    {"ERIC", vector<Data *>()},      {"ESTHER", vector<Data *>()},
    {"ETHAN", vector<Data *>()},     {"EVA", vector<Data *>()},
    {"EVAN", vector<Data *>()},      {"EVELYN", vector<Data *>()},
    {"EVERETT", vector<Data *>()},   {"EVERLY", vector<Data *>()},
    {"EZEKIEL", vector<Data *>()},   {"EZRA", vector<Data *>()},
    {"FAITH", vector<Data *>()},     {"FELIX", vector<Data *>()},
    {"FINLEY", vector<Data *>()},    {"FINN", vector<Data *>()},
    {"FIONA", vector<Data *>()},     {"GABRIEL", vector<Data *>()},
    {"GABRIELLA", vector<Data *>()}, {"GAEL", vector<Data *>()},
    {"GAVIN", vector<Data *>()},     {"GENESIS", vector<Data *>()},
    {"GENEVIEVE", vector<Data *>()}, {"GEORGE", vector<Data *>()},
    {"GEORGIA", vector<Data *>()},   {"GIANNA", vector<Data *>()},
    {"GIOVANNI", vector<Data *>()},  {"GRACE", vector<Data *>()},
    {"GRACIE", vector<Data *>()},    {"GRAHAM", vector<Data *>()},
    {"GRANT", vector<Data *>()},     {"GRAYSON", vector<Data *>()},
    {"GREYSON", vector<Data *>()},   {"GRIFFIN", vector<Data *>()},
    {"HADLEY", vector<Data *>()},    {"HAILEY", vector<Data *>()},
    {"HANNAH", vector<Data *>()},    {"HARLEY", vector<Data *>()},
    {"HARMONY", vector<Data *>()},   {"HARPER", vector<Data *>()},
    {"HARRISON", vector<Data *>()},  {"HAYDEN", vector<Data *>()},
    {"HAZEL", vector<Data *>()},     {"HENRY", vector<Data *>()},
    {"HOLDEN", vector<Data *>()},    {"HUDSON", vector<Data *>()},
    {"HUNTER", vector<Data *>()},    {"IAN", vector<Data *>()},
    {"IRIS", vector<Data *>()},      {"ISAAC", vector<Data *>()},
    {"ISABEL", vector<Data *>()},    {"ISABELLA", vector<Data *>()},
    {"ISABELLE", vector<Data *>()},  {"ISAIAH", vector<Data *>()},
    {"ISLA", vector<Data *>()},      {"ISRAEL", vector<Data *>()},
    {"IVAN", vector<Data *>()},      {"IVY", vector<Data *>()},
    {"JACE", vector<Data *>()},      {"JACK", vector<Data *>()},
    {"JACKSON", vector<Data *>()},   {"JACOB", vector<Data *>()},
    {"JADE", vector<Data *>()},      {"JADEN", vector<Data *>()},
    {"JAKE", vector<Data *>()},      {"JAMES", vector<Data *>()},
    {"JAMESON", vector<Data *>()},   {"JASMINE", vector<Data *>()},
    {"JASON", vector<Data *>()},     {"JASPER", vector<Data *>()},
    {"JAVIER", vector<Data *>()},    {"JAX", vector<Data *>()},
    {"JAXON", vector<Data *>()},     {"JAXSON", vector<Data *>()},
    {"JAYCE", vector<Data *>()},     {"JAYDEN", vector<Data *>()},
    {"JAYLA", vector<Data *>()},     {"JEREMIAH", vector<Data *>()},
    {"JEREMY", vector<Data *>()},    {"JESSE", vector<Data *>()},
    {"JESSICA", vector<Data *>()},   {"JESUS", vector<Data *>()},
    {"JOANNA", vector<Data *>()},    {"JOCELYN", vector<Data *>()},
    {"JOEL", vector<Data *>()},      {"JOHN", vector<Data *>()},
    {"JONAH", vector<Data *>()},     {"JONATHAN", vector<Data *>()},
    {"JORDAN", vector<Data *>()},    {"JORDYN", vector<Data *>()},
    {"JORGE", vector<Data *>()},     {"JOSE", vector<Data *>()},
    {"JOSEPH", vector<Data *>()},    {"JOSEPHINE", vector<Data *>()},
    {"JOSHUA", vector<Data *>()},    {"JOSIAH", vector<Data *>()},
    {"JOSIE", vector<Data *>()},     {"JOSUE", vector<Data *>()},
    {"JUAN", vector<Data *>()},      {"JUDAH", vector<Data *>()},
    {"JUDE", vector<Data *>()},      {"JULIA", vector<Data *>()},
    {"JULIAN", vector<Data *>()},    {"JULIANA", vector<Data *>()},
    {"JULIANNA", vector<Data *>()},  {"JULIET", vector<Data *>()},
    {"JULIETTE", vector<Data *>()},  {"JUNE", vector<Data *>()},
    {"JUSTIN", vector<Data *>()},    {"KADEN", vector<Data *>()},
    {"KAI", vector<Data *>()},       {"KAIDEN", vector<Data *>()},
    {"KALEB", vector<Data *>()},     {"KARTER", vector<Data *>()},
    {"KATHERINE", vector<Data *>()}, {"KAYDEN", vector<Data *>()},
    {"KAYLA", vector<Data *>()},     {"KAYLEE", vector<Data *>()},
    {"KENDALL", vector<Data *>()},   {"KENNEDY", vector<Data *>()},
    {"KENNETH", vector<Data *>()},   {"KEVIN", vector<Data *>()},
    {"KHLOE", vector<Data *>()},     {"KILLIAN", vector<Data *>()},
    {"KIMBERLY", vector<Data *>()},  {"KING", vector<Data *>()},
    {"KINGSTON", vector<Data *>()},  {"KINSLEY", vector<Data *>()},
    {"KNOX", vector<Data *>()},      {"KYLE", vector<Data *>()},
    {"KYLIE", vector<Data *>()},     {"KYRIE", vector<Data *>()},
    {"LAILA", vector<Data *>()},     {"LANDON", vector<Data *>()},
    {"LAUREN", vector<Data *>()},    {"LAYLA", vector<Data *>()},
    {"LEAH", vector<Data *>()},      {"LEILA", vector<Data *>()},
    {"LEILANI", vector<Data *>()},   {"LEO", vector<Data *>()},
    {"LEON", vector<Data *>()},      {"LEONARDO", vector<Data *>()},
    {"LEVI", vector<Data *>()},      {"LIAM", vector<Data *>()},
    {"LILA", vector<Data *>()},      {"LILIANA", vector<Data *>()},
    {"LILLIAN", vector<Data *>()},   {"LILLY", vector<Data *>()},
    {"LILY", vector<Data *>()},      {"LINCOLN", vector<Data *>()},
    {"LOGAN", vector<Data *>()},     {"LOLA", vector<Data *>()},
    {"LONDON", vector<Data *>()},    {"LONDYN", vector<Data *>()},
    {"LORENZO", vector<Data *>()},   {"LUCA", vector<Data *>()},
    {"LUCAS", vector<Data *>()},     {"LUCIA", vector<Data *>()},
    {"LUCY", vector<Data *>()},      {"LUIS", vector<Data *>()},
    {"LUKAS", vector<Data *>()},     {"LUKE", vector<Data *>()},
    {"LUNA", vector<Data *>()},      {"LYDIA", vector<Data *>()},
    {"LYLA", vector<Data *>()},      {"MACKENZIE", vector<Data *>()},
    {"MADDOX", vector<Data *>()},    {"MADELINE", vector<Data *>()},
    {"MADELYN", vector<Data *>()},   {"MADISON", vector<Data *>()},
    {"MAGGIE", vector<Data *>()},    {"MAKAYLA", vector<Data *>()},
    {"MALACHI", vector<Data *>()},   {"MALIA", vector<Data *>()},
    {"MARCUS", vector<Data *>()},    {"MARGARET", vector<Data *>()},
    {"MARIA", vector<Data *>()},     {"MARIAH", vector<Data *>()},
    {"MARK", vector<Data *>()},      {"MARLEY", vector<Data *>()},
    {"MARY", vector<Data *>()},      {"MASON", vector<Data *>()},
    {"MATEO", vector<Data *>()},     {"MATIAS", vector<Data *>()},
    {"MATTEO", vector<Data *>()},    {"MATTHEW", vector<Data *>()},
    {"MAVERICK", vector<Data *>()},  {"MAX", vector<Data *>()},
    {"MAXIMUS", vector<Data *>()},   {"MAXWELL", vector<Data *>()},
    {"MAYA", vector<Data *>()},      {"MCKENZIE", vector<Data *>()},
    {"MELANIE", vector<Data *>()},   {"MELODY", vector<Data *>()},
    {"MESSIAH", vector<Data *>()},   {"MIA", vector<Data *>()},
    {"MICAH", vector<Data *>()},     {"MICHAEL", vector<Data *>()},
    {"MICHELLE", vector<Data *>()},  {"MIGUEL", vector<Data *>()},
    {"MILA", vector<Data *>()},      {"MILES", vector<Data *>()},
    {"MILO", vector<Data *>()},      {"MOLLY", vector<Data *>()},
    {"MORGAN", vector<Data *>()},    {"MYA", vector<Data *>()},
    {"MYLES", vector<Data *>()},     {"NAOMI", vector<Data *>()},
    {"NATALIA", vector<Data *>()},   {"NATALIE", vector<Data *>()},
    {"NATHAN", vector<Data *>()},    {"NATHANIEL", vector<Data *>()},
    {"NEVAEH", vector<Data *>()},    {"NICHOLAS", vector<Data *>()},
    {"NICOLAS", vector<Data *>()},   {"NICOLE", vector<Data *>()},
    {"NOAH", vector<Data *>()},      {"NOELLE", vector<Data *>()},
    {"NOLAN", vector<Data *>()},     {"NORA", vector<Data *>()},
    {"NORAH", vector<Data *>()},     {"NOVA", vector<Data *>()},
    {"OLIVER", vector<Data *>()},    {"OLIVIA", vector<Data *>()},
    {"OMAR", vector<Data *>()},      {"OSCAR", vector<Data *>()},
    {"OWEN", vector<Data *>()},      {"PAIGE", vector<Data *>()},
    {"PAISLEY", vector<Data *>()},   {"PARKER", vector<Data *>()},
    {"PATRICK", vector<Data *>()},   {"PAUL", vector<Data *>()},
    {"PAXTON", vector<Data *>()},    {"PAYTON", vector<Data *>()},
    {"PENELOPE", vector<Data *>()},  {"PETER", vector<Data *>()},
    {"PEYTON", vector<Data *>()},    {"PIPER", vector<Data *>()},
    {"PRESLEY", vector<Data *>()},   {"PRESTON", vector<Data *>()},
    {"QUINN", vector<Data *>()},     {"RACHEL", vector<Data *>()},
    {"RAELYNN", vector<Data *>()},   {"REAGAN", vector<Data *>()},
    {"REBECCA", vector<Data *>()},   {"REESE", vector<Data *>()},
    {"REMI", vector<Data *>()},      {"REMINGTON", vector<Data *>()},
    {"RHETT", vector<Data *>()},     {"RICHARD", vector<Data *>()},
    {"RILEY", vector<Data *>()},     {"RIVER", vector<Data *>()},
    {"ROBERT", vector<Data *>()},    {"ROMAN", vector<Data *>()},
    {"ROSALIE", vector<Data *>()},   {"ROSE", vector<Data *>()},
    {"ROWAN", vector<Data *>()},     {"RUBY", vector<Data *>()},
    {"RYAN", vector<Data *>()},      {"RYDER", vector<Data *>()},
    {"RYKER", vector<Data *>()},     {"RYLEE", vector<Data *>()},
    {"RYLEIGH", vector<Data *>()},   {"SADIE", vector<Data *>()},
    {"SAMANTHA", vector<Data *>()},  {"SAMUEL", vector<Data *>()},
    {"SANTIAGO", vector<Data *>()},  {"SARA", vector<Data *>()},
    {"SARAH", vector<Data *>()},     {"SAVANNAH", vector<Data *>()},
    {"SAWYER", vector<Data *>()},    {"SCARLETT", vector<Data *>()},
    {"SEBASTIAN", vector<Data *>()}, {"SELENA", vector<Data *>()},
    {"SERENITY", vector<Data *>()},  {"SIENNA", vector<Data *>()},
    {"SILAS", vector<Data *>()},     {"SKYLAR", vector<Data *>()},
    {"SLOANE", vector<Data *>()},    {"SOFIA", vector<Data *>()},
    {"SOPHIA", vector<Data *>()},    {"SOPHIE", vector<Data *>()},
    {"STELLA", vector<Data *>()},    {"STEVEN", vector<Data *>()},
    {"SUMMER", vector<Data *>()},    {"SYDNEY", vector<Data *>()},
    {"TAYLOR", vector<Data *>()},    {"TEAGAN", vector<Data *>()},
    {"TESSA", vector<Data *>()},     {"THEODORE", vector<Data *>()},
    {"THIAGO", vector<Data *>()},    {"THOMAS", vector<Data *>()},
    {"TIMOTHY", vector<Data *>()},   {"TRINITY", vector<Data *>()},
    {"TRISTAN", vector<Data *>()},   {"TUCKER", vector<Data *>()},
    {"TYLER", vector<Data *>()},     {"VALENTINA", vector<Data *>()},
    {"VALERIA", vector<Data *>()},   {"VALERIE", vector<Data *>()},
    {"VANESSA", vector<Data *>()},   {"VICTOR", vector<Data *>()},
    {"VICTORIA", vector<Data *>()},  {"VINCENT", vector<Data *>()},
    {"VIOLET", vector<Data *>()},    {"VIVIAN", vector<Data *>()},
    {"WAYLON", vector<Data *>()},    {"WESLEY", vector<Data *>()},
    {"WESTON", vector<Data *>()},    {"WILLIAM", vector<Data *>()},
    {"WILLOW", vector<Data *>()},    {"WYATT", vector<Data *>()},
    {"XANDER", vector<Data *>()},    {"XAVIER", vector<Data *>()},
    {"XIMENA", vector<Data *>()},    {"ZACHARY", vector<Data *>()},
    {"ZANDER", vector<Data *>()},    {"ZANE", vector<Data *>()},
    {"ZAYDEN", vector<Data *>()},    {"ZION", vector<Data *>()},
    {"ZOE", vector<Data *>()},       {"ZOEY", vector<Data *>()}};
unordered_map<string, vector<Data *>> secondNamesMap = {
    {"ACOSTA", vector<Data *>()},      {"ADAMS", vector<Data *>()},
    {"ADKINS", vector<Data *>()},      {"AGUILAR", vector<Data *>()},
    {"AGUIRRE", vector<Data *>()},     {"ALEXANDER", vector<Data *>()},
    {"ALLEN", vector<Data *>()},       {"ALVARADO", vector<Data *>()},
    {"ALVAREZ", vector<Data *>()},     {"ANDERSON", vector<Data *>()},
    {"ANDREWS", vector<Data *>()},     {"ARMSTRONG", vector<Data *>()},
    {"ARNOLD", vector<Data *>()},      {"AUSTIN", vector<Data *>()},
    {"AVILA", vector<Data *>()},       {"AYALA", vector<Data *>()},
    {"BAILEY", vector<Data *>()},      {"BAKER", vector<Data *>()},
    {"BALDWIN", vector<Data *>()},     {"BANKS", vector<Data *>()},
    {"BARBER", vector<Data *>()},      {"BARKER", vector<Data *>()},
    {"BARNES", vector<Data *>()},      {"BARNETT", vector<Data *>()},
    {"BARRETT", vector<Data *>()},     {"BARTON", vector<Data *>()},
    {"BATES", vector<Data *>()},       {"BECK", vector<Data *>()},
    {"BECKER", vector<Data *>()},      {"BELL", vector<Data *>()},
    {"BENNETT", vector<Data *>()},     {"BENSON", vector<Data *>()},
    {"BERRY", vector<Data *>()},       {"BISHOP", vector<Data *>()},
    {"BLACK", vector<Data *>()},       {"BLAIR", vector<Data *>()},
    {"BLAKE", vector<Data *>()},       {"BOWEN", vector<Data *>()},
    {"BOWMAN", vector<Data *>()},      {"BOYD", vector<Data *>()},
    {"BRADLEY", vector<Data *>()},     {"BRADY", vector<Data *>()},
    {"BREWER", vector<Data *>()},      {"BROOKS", vector<Data *>()},
    {"BROWN", vector<Data *>()},       {"BRYANT", vector<Data *>()},
    {"BURGESS", vector<Data *>()},     {"BURKE", vector<Data *>()},
    {"BURNS", vector<Data *>()},       {"BURTON", vector<Data *>()},
    {"BUSH", vector<Data *>()},        {"BUTLER", vector<Data *>()},
    {"BYRD", vector<Data *>()},        {"CABRERA", vector<Data *>()},
    {"CALDERON", vector<Data *>()},    {"CALDWELL", vector<Data *>()},
    {"CAMACHO", vector<Data *>()},     {"CAMPBELL", vector<Data *>()},
    {"CAMPOS", vector<Data *>()},      {"CANNON", vector<Data *>()},
    {"CARDENAS", vector<Data *>()},    {"CARLSON", vector<Data *>()},
    {"CARPENTER", vector<Data *>()},   {"CARR", vector<Data *>()},
    {"CARRILLO", vector<Data *>()},    {"CARROLL", vector<Data *>()},
    {"CARTER", vector<Data *>()},      {"CASTANEDA", vector<Data *>()},
    {"CASTILLO", vector<Data *>()},    {"CASTRO", vector<Data *>()},
    {"CERVANTES", vector<Data *>()},   {"CHAMBERS", vector<Data *>()},
    {"CHAN", vector<Data *>()},        {"CHANDLER", vector<Data *>()},
    {"CHANG", vector<Data *>()},       {"CHAPMAN", vector<Data *>()},
    {"CHAVEZ", vector<Data *>()},      {"CHEN", vector<Data *>()},
    {"CHRISTENSEN", vector<Data *>()}, {"CLARK", vector<Data *>()},
    {"CLARKE", vector<Data *>()},      {"COHEN", vector<Data *>()},
    {"COLE", vector<Data *>()},        {"COLEMAN", vector<Data *>()},
    {"COLLINS", vector<Data *>()},     {"COLON", vector<Data *>()},
    {"CONTRERAS", vector<Data *>()},   {"COOK", vector<Data *>()},
    {"COOPER", vector<Data *>()},      {"CORTEZ", vector<Data *>()},
    {"COX", vector<Data *>()},         {"CRAIG", vector<Data *>()},
    {"CRAWFORD", vector<Data *>()},    {"CROSS", vector<Data *>()},
    {"CRUZ", vector<Data *>()},        {"CUMMINGS", vector<Data *>()},
    {"CUNNINGHAM", vector<Data *>()},  {"CURRY", vector<Data *>()},
    {"CURTIS", vector<Data *>()},      {"DANIEL", vector<Data *>()},
    {"DANIELS", vector<Data *>()},     {"DAVIDSON", vector<Data *>()},
    {"DAVIS", vector<Data *>()},       {"DAWSON", vector<Data *>()},
    {"DAY", vector<Data *>()},         {"DEAN", vector<Data *>()},
    {"DELACRUZ", vector<Data *>()},    {"DELEON", vector<Data *>()},
    {"DELGADO", vector<Data *>()},     {"DENNIS", vector<Data *>()},
    {"DIAZ", vector<Data *>()},        {"DIXON", vector<Data *>()},
    {"DOMINGUEZ", vector<Data *>()},   {"DOUGLAS", vector<Data *>()},
    {"DOYLE", vector<Data *>()},       {"DUNCAN", vector<Data *>()},
    {"DUNN", vector<Data *>()},        {"DURAN", vector<Data *>()},
    {"EDWARDS", vector<Data *>()},     {"ELLIOTT", vector<Data *>()},
    {"ELLIS", vector<Data *>()},       {"ERICKSON", vector<Data *>()},
    {"ESPINOZA", vector<Data *>()},    {"ESTRADA", vector<Data *>()},
    {"EVANS", vector<Data *>()},       {"FARMER", vector<Data *>()},
    {"FERGUSON", vector<Data *>()},    {"FERNANDEZ", vector<Data *>()},
    {"FIELDS", vector<Data *>()},      {"FIGUEROA", vector<Data *>()},
    {"FISCHER", vector<Data *>()},     {"FISHER", vector<Data *>()},
    {"FITZGERALD", vector<Data *>()},  {"FLEMING", vector<Data *>()},
    {"FLETCHER", vector<Data *>()},    {"FLORES", vector<Data *>()},
    {"FORD", vector<Data *>()},        {"FOSTER", vector<Data *>()},
    {"FOWLER", vector<Data *>()},      {"FOX", vector<Data *>()},
    {"FRANCIS", vector<Data *>()},     {"FRANCO", vector<Data *>()},
    {"FRANK", vector<Data *>()},       {"FRANKLIN", vector<Data *>()},
    {"FRAZIER", vector<Data *>()},     {"FREEMAN", vector<Data *>()},
    {"FUENTES", vector<Data *>()},     {"FULLER", vector<Data *>()},
    {"GALLAGHER", vector<Data *>()},   {"GALLEGOS", vector<Data *>()},
    {"GARCIA", vector<Data *>()},      {"GARDNER", vector<Data *>()},
    {"GARNER", vector<Data *>()},      {"GARRETT", vector<Data *>()},
    {"GARZA", vector<Data *>()},       {"GEORGE", vector<Data *>()},
    {"GIBSON", vector<Data *>()},      {"GILBERT", vector<Data *>()},
    {"GILL", vector<Data *>()},        {"GOMEZ", vector<Data *>()},
    {"GONZALES", vector<Data *>()},    {"GONZALEZ", vector<Data *>()},
    {"GOODMAN", vector<Data *>()},     {"GOODWIN", vector<Data *>()},
    {"GORDON", vector<Data *>()},      {"GRAHAM", vector<Data *>()},
    {"GRANT", vector<Data *>()},       {"GRAVES", vector<Data *>()},
    {"GRAY", vector<Data *>()},        {"GREEN", vector<Data *>()},
    {"GREENE", vector<Data *>()},      {"GREGORY", vector<Data *>()},
    {"GRIFFIN", vector<Data *>()},     {"GRIFFITH", vector<Data *>()},
    {"GROSS", vector<Data *>()},       {"GUERRA", vector<Data *>()},
    {"GUERRERO", vector<Data *>()},    {"GUTIERREZ", vector<Data *>()},
    {"GUZMAN", vector<Data *>()},      {"HAIL", vector<Data *>()},
    {"HALE", vector<Data *>()},        {"HALL", vector<Data *>()},
    {"HAMILTON", vector<Data *>()},    {"HAMMOND", vector<Data *>()},
    {"HAMPTON", vector<Data *>()},     {"HANSEN", vector<Data *>()},
    {"HANSON", vector<Data *>()},      {"HARDY", vector<Data *>()},
    {"HARMON", vector<Data *>()},      {"HARPER", vector<Data *>()},
    {"HARRINGTON", vector<Data *>()},  {"HARRIS", vector<Data *>()},
    {"HARRISON", vector<Data *>()},    {"HART", vector<Data *>()},
    {"HARVEY", vector<Data *>()},      {"HAWKINS", vector<Data *>()},
    {"HAYES", vector<Data *>()},       {"HAYNES", vector<Data *>()},
    {"HENDERSON", vector<Data *>()},   {"HENRY", vector<Data *>()},
    {"HERNANDEZ", vector<Data *>()},   {"HERRERA", vector<Data *>()},
    {"HICKS", vector<Data *>()},       {"HIGGINS", vector<Data *>()},
    {"HILL", vector<Data *>()},        {"HINES", vector<Data *>()},
    {"HODGES", vector<Data *>()},      {"HOFFMAN", vector<Data *>()},
    {"HOLLAND", vector<Data *>()},     {"HOLMES", vector<Data *>()},
    {"HOLT", vector<Data *>()},        {"HOPKINS", vector<Data *>()},
    {"HORTON", vector<Data *>()},      {"HOWARD", vector<Data *>()},
    {"HOWELL", vector<Data *>()},      {"HUANG", vector<Data *>()},
    {"HUBBARD", vector<Data *>()},     {"HUDSON", vector<Data *>()},
    {"HUGHES", vector<Data *>()},      {"HUNT", vector<Data *>()},
    {"HUNTER", vector<Data *>()},      {"INGRAM", vector<Data *>()},
    {"JACKSON", vector<Data *>()},     {"JACOBS", vector<Data *>()},
    {"JAMES", vector<Data *>()},       {"JENKINS", vector<Data *>()},
    {"JENNINGS", vector<Data *>()},    {"JENSEN", vector<Data *>()},
    {"JIMENEZ", vector<Data *>()},     {"JOHNSON", vector<Data *>()},
    {"JOHNSTON", vector<Data *>()},    {"JONES", vector<Data *>()},
    {"JORDAN", vector<Data *>()},      {"JOSEPH", vector<Data *>()},
    {"JUAREZ", vector<Data *>()},      {"KELLER", vector<Data *>()},
    {"KELLEY", vector<Data *>()},      {"KELLY", vector<Data *>()},
    {"KENNEDY", vector<Data *>()},     {"KHAN", vector<Data *>()},
    {"KIM", vector<Data *>()},         {"KING", vector<Data *>()},
    {"KLEIN", vector<Data *>()},       {"KNIGHT", vector<Data *>()},
    {"LAMBERT", vector<Data *>()},     {"LANE", vector<Data *>()},
    {"LARA", vector<Data *>()},        {"LARSON", vector<Data *>()},
    {"LAWRENCE", vector<Data *>()},    {"LAWSON", vector<Data *>()},
    {"LE", vector<Data *>()},          {"LEE", vector<Data *>()},
    {"LEON", vector<Data *>()},        {"LEONARD", vector<Data *>()},
    {"LEWIS", vector<Data *>()},       {"LI", vector<Data *>()},
    {"LIN", vector<Data *>()},         {"LITTLE", vector<Data *>()},
    {"LIU", vector<Data *>()},         {"LOGAN", vector<Data *>()},
    {"LONG", vector<Data *>()},        {"LOPEZ", vector<Data *>()},
    {"LOVE", vector<Data *>()},        {"LOWE", vector<Data *>()},
    {"LUCAS", vector<Data *>()},       {"LUNA", vector<Data *>()},
    {"LYNCH", vector<Data *>()},       {"LYONS", vector<Data *>()},
    {"MACK", vector<Data *>()},        {"MALDONADO", vector<Data *>()},
    {"MALONE", vector<Data *>()},      {"MANN", vector<Data *>()},
    {"MANNING", vector<Data *>()},     {"MARQUEZ", vector<Data *>()},
    {"MARSHALL", vector<Data *>()},    {"MARTIN", vector<Data *>()},
    {"MARTINEZ", vector<Data *>()},    {"MASON", vector<Data *>()},
    {"MATTHEWS", vector<Data *>()},    {"MAXWELL", vector<Data *>()},
    {"MAY", vector<Data *>()},         {"MCCARTHY", vector<Data *>()},
    {"MCCOY", vector<Data *>()},       {"MCDANIEL", vector<Data *>()},
    {"MCDONALD", vector<Data *>()},    {"MCGEE", vector<Data *>()},
    {"MCKINNEY", vector<Data *>()},    {"MCLAUGHLIN", vector<Data *>()},
    {"MEDINA", vector<Data *>()},      {"MEJIA", vector<Data *>()},
    {"MENDEZ", vector<Data *>()},      {"MENDOZA", vector<Data *>()},
    {"MEYER", vector<Data *>()},       {"MILES", vector<Data *>()},
    {"MILLER", vector<Data *>()},      {"MILLS", vector<Data *>()},
    {"MIRANDA", vector<Data *>()},     {"MITCHELL", vector<Data *>()},
    {"MOLINA", vector<Data *>()},      {"MONTGOMERY", vector<Data *>()},
    {"MONTOYA", vector<Data *>()},     {"MOORE", vector<Data *>()},
    {"MORALES", vector<Data *>()},     {"MORAN", vector<Data *>()},
    {"MORENO", vector<Data *>()},      {"MORGAN", vector<Data *>()},
    {"MORRIS", vector<Data *>()},      {"MORRISON", vector<Data *>()},
    {"MOSS", vector<Data *>()},        {"MULLINS", vector<Data *>()},
    {"MUNOZ", vector<Data *>()},       {"MURPHY", vector<Data *>()},
    {"MURRAY", vector<Data *>()},      {"MYERS", vector<Data *>()},
    {"NAVARRO", vector<Data *>()},     {"NEAL", vector<Data *>()},
    {"NELSON", vector<Data *>()},      {"NEWMAN", vector<Data *>()},
    {"NEWTON", vector<Data *>()},      {"NGUYEN", vector<Data *>()},
    {"NICHOLS", vector<Data *>()},     {"NORMAN", vector<Data *>()},
    {"NORRIS", vector<Data *>()},      {"NUNEZ", vector<Data *>()},
    {"OBRIEN", vector<Data *>()},      {"OCHOA", vector<Data *>()},
    {"OCONNOR", vector<Data *>()},     {"OLIVER", vector<Data *>()},
    {"OLSON", vector<Data *>()},       {"ORTEGA", vector<Data *>()},
    {"ORTIZ", vector<Data *>()},       {"OWENS", vector<Data *>()},
    {"PACHECO", vector<Data *>()},     {"PADILLA", vector<Data *>()},
    {"PAGE", vector<Data *>()},        {"PALMER", vector<Data *>()},
    {"PARK", vector<Data *>()},        {"PARKER", vector<Data *>()},
    {"PARKS", vector<Data *>()},       {"PARSONS", vector<Data *>()},
    {"PATEL", vector<Data *>()},       {"PATTERSON", vector<Data *>()},
    {"PAUL", vector<Data *>()},        {"PAYNE", vector<Data *>()},
    {"PEARSON", vector<Data *>()},     {"PENA", vector<Data *>()},
    {"PEREZ", vector<Data *>()},       {"PERKINS", vector<Data *>()},
    {"PERRY", vector<Data *>()},       {"PERSON", vector<Data *>()},
    {"PETERS", vector<Data *>()},      {"PETERSON", vector<Data *>()},
    {"PHAM", vector<Data *>()},        {"PHILLIPS", vector<Data *>()},
    {"PIERCE", vector<Data *>()},      {"PORTER", vector<Data *>()},
    {"POTTER", vector<Data *>()},      {"POWELL", vector<Data *>()},
    {"POWERS", vector<Data *>()},      {"PRICE", vector<Data *>()},
    {"QUINN", vector<Data *>()},       {"RAMIREZ", vector<Data *>()},
    {"RAMOS", vector<Data *>()},       {"RAMSEY", vector<Data *>()},
    {"RAY", vector<Data *>()},         {"REED", vector<Data *>()},
    {"REESE", vector<Data *>()},       {"REEVES", vector<Data *>()},
    {"REID", vector<Data *>()},        {"REYES", vector<Data *>()},
    {"REYNOLDS", vector<Data *>()},    {"RHODES", vector<Data *>()},
    {"RICE", vector<Data *>()},        {"RICHARDS", vector<Data *>()},
    {"RICHARDSON", vector<Data *>()},  {"RILEY", vector<Data *>()},
    {"RIOS", vector<Data *>()},        {"RIVAS", vector<Data *>()},
    {"RIVERA", vector<Data *>()},      {"ROBBINS", vector<Data *>()},
    {"ROBERTS", vector<Data *>()},     {"ROBERTSON", vector<Data *>()},
    {"ROBINSON", vector<Data *>()},    {"ROBLES", vector<Data *>()},
    {"RODGERS", vector<Data *>()},     {"RODRIGUEZ", vector<Data *>()},
    {"ROGERS", vector<Data *>()},      {"ROJAS", vector<Data *>()},
    {"ROMAN", vector<Data *>()},       {"ROMERO", vector<Data *>()},
    {"ROSALES", vector<Data *>()},     {"ROSE", vector<Data *>()},
    {"ROSS", vector<Data *>()},        {"ROWE", vector<Data *>()},
    {"RUIZ", vector<Data *>()},        {"RUSSELL", vector<Data *>()},
    {"RYAN", vector<Data *>()},        {"SALAZAR", vector<Data *>()},
    {"SALINAS", vector<Data *>()},     {"SANCHEZ", vector<Data *>()},
    {"SANDERS", vector<Data *>()},     {"SANDOVAL", vector<Data *>()},
    {"SANTIAGO", vector<Data *>()},    {"SANTOS", vector<Data *>()},
    {"SAUNDERS", vector<Data *>()},    {"SCHMIDT", vector<Data *>()},
    {"SCHNEIDER", vector<Data *>()},   {"SCHROEDER", vector<Data *>()},
    {"SCHULTZ", vector<Data *>()},     {"SCHWARTZ", vector<Data *>()},
    {"SCOTT", vector<Data *>()},       {"SERRANO", vector<Data *>()},
    {"SHARP", vector<Data *>()},       {"SHAW", vector<Data *>()},
    {"SHELTON", vector<Data *>()},     {"SHERMAN", vector<Data *>()},
    {"SILVA", vector<Data *>()},       {"SIMMONS", vector<Data *>()},
    {"SIMON", vector<Data *>()},       {"SIMPSON", vector<Data *>()},
    {"SIMS", vector<Data *>()},        {"SINGH", vector<Data *>()},
    {"SMITH", vector<Data *>()},       {"SNYDER", vector<Data *>()},
    {"SOLIS", vector<Data *>()},       {"SOTO", vector<Data *>()},
    {"SPENCER", vector<Data *>()},     {"STANLEY", vector<Data *>()},
    {"STEELE", vector<Data *>()},      {"STEPHENS", vector<Data *>()},
    {"STEVENS", vector<Data *>()},     {"STEVENSON", vector<Data *>()},
    {"STEWART", vector<Data *>()},     {"STONE", vector<Data *>()},
    {"STRICKLAND", vector<Data *>()},  {"SULLIVAN", vector<Data *>()},
    {"SUTTON", vector<Data *>()},      {"SWANSON", vector<Data *>()},
    {"TATE", vector<Data *>()},        {"TAYLOR", vector<Data *>()},
    {"TERRY", vector<Data *>()},       {"THOMAS", vector<Data *>()},
    {"THOMPSON", vector<Data *>()},    {"THORNTON", vector<Data *>()},
    {"TODD", vector<Data *>()},        {"TORRES", vector<Data *>()},
    {"TOWNSEND", vector<Data *>()},    {"TRAN", vector<Data *>()},
    {"TRUJILLO", vector<Data *>()},    {"TUCKER", vector<Data *>()},
    {"TURNER", vector<Data *>()},      {"VALDEZ", vector<Data *>()},
    {"VALENCIA", vector<Data *>()},    {"VARGAS", vector<Data *>()},
    {"VASQUEZ", vector<Data *>()},     {"VAUGHN", vector<Data *>()},
    {"VAZQUEZ", vector<Data *>()},     {"VEGA", vector<Data *>()},
    {"VELASQUEZ", vector<Data *>()},   {"WADE", vector<Data *>()},
    {"WAGNER", vector<Data *>()},      {"WALKER", vector<Data *>()},
    {"WALLACE", vector<Data *>()},     {"WALSH", vector<Data *>()},
    {"WALTERS", vector<Data *>()},     {"WALTON", vector<Data *>()},
    {"WANG", vector<Data *>()},        {"WARD", vector<Data *>()},
    {"WARNER", vector<Data *>()},      {"WARREN", vector<Data *>()},
    {"WASHINGTON", vector<Data *>()},  {"WATERS", vector<Data *>()},
    {"WATKINS", vector<Data *>()},     {"WATSON", vector<Data *>()},
    {"WATTS", vector<Data *>()},       {"WEAVER", vector<Data *>()},
    {"WEBB", vector<Data *>()},        {"WEBER", vector<Data *>()},
    {"WEBSTER", vector<Data *>()},     {"WELCH", vector<Data *>()},
    {"WELLS", vector<Data *>()},       {"WEST", vector<Data *>()},
    {"WHEELER", vector<Data *>()},     {"WHITE", vector<Data *>()},
    {"WILLIAMS", vector<Data *>()},    {"WILLIAMSON", vector<Data *>()},
    {"WILLIS", vector<Data *>()},      {"WILSON", vector<Data *>()},
    {"WISE", vector<Data *>()},        {"WOLF", vector<Data *>()},
    {"WOLFE", vector<Data *>()},       {"WONG", vector<Data *>()},
    {"WOOD", vector<Data *>()},        {"WOODS", vector<Data *>()},
    {"WRIGHT", vector<Data *>()},      {"WU", vector<Data *>()},
    {"YANG", vector<Data *>()},        {"YOUNG", vector<Data *>()},
    {"ZHANG", vector<Data *>()},       {"ZIMMERMAN", vector<Data *>()}};
Data xst[500];
unordered_map<string, int> firstNamesOrdered = {
    {"AALIYAH", 0},     {"AARON", 1},       {"ABEL", 2},
    {"ABIGAIL", 3},     {"ABRAHAM", 4},     {"ADALINE", 5},
    {"ADALYN", 6},      {"ADALYNN", 7},     {"ADAM", 8},
    {"ADDISON", 9},     {"ADELINE", 10},    {"ADELYN", 11},
    {"ADRIAN", 12},     {"ADRIANA", 13},    {"AIDAN", 14},
    {"AIDEN", 15},      {"ALAINA", 16},     {"ALAN", 17},
    {"ALANA", 18},      {"ALAYNA", 19},     {"ALEJANDRO", 20},
    {"ALEX", 21},       {"ALEXA", 22},      {"ALEXANDER", 23},
    {"ALEXANDRA", 24},  {"ALEXIS", 25},     {"ALICE", 26},
    {"ALINA", 27},      {"ALIVIA", 28},     {"ALIYAH", 29},
    {"ALLISON", 30},    {"ALYSSA", 31},     {"AMARA", 32},
    {"AMAYA", 33},      {"AMELIA", 34},     {"AMIR", 35},
    {"AMY", 36},        {"ANA", 37},        {"ANASTASIA", 38},
    {"ANDREA", 39},     {"ANDRES", 40},     {"ANDREW", 41},
    {"ANGEL", 42},      {"ANGELA", 43},     {"ANGELINA", 44},
    {"ANNA", 45},       {"ANNABELLE", 46},  {"ANTHONY", 47},
    {"ANTONIO", 48},    {"ARABELLA", 49},   {"ARIA", 50},
    {"ARIANA", 51},     {"ARIANNA", 52},    {"ARIEL", 53},
    {"ARTHUR", 54},     {"ARYA", 55},       {"ASHER", 56},
    {"ASHLEY", 57},     {"ASHTON", 58},     {"ATHENA", 59},
    {"AUBREE", 60},     {"AUBREY", 61},     {"AUDREY", 62},
    {"AUGUST", 63},     {"AURORA", 64},     {"AUSTIN", 65},
    {"AUTUMN", 66},     {"AVA", 67},        {"AVERY", 68},
    {"AXEL", 69},       {"AYDEN", 70},      {"AYLA", 71},
    {"BAILEY", 72},     {"BARRETT", 73},    {"BEAU", 74},
    {"BECKETT", 75},    {"BELLA", 76},      {"BENJAMIN", 77},
    {"BENNETT", 78},    {"BENTLEY", 79},    {"BLAKE", 80},
    {"BRADLEY", 81},    {"BRADY", 82},      {"BRANDON", 83},
    {"BRANTLEY", 84},   {"BRAXTON", 85},    {"BRAYDEN", 86},
    {"BRIAN", 87},      {"BRIANNA", 88},    {"BRIELLE", 89},
    {"BRODY", 90},      {"BROOKE", 91},     {"BROOKLYN", 92},
    {"BROOKLYNN", 93},  {"BROOKS", 94},     {"BRYAN", 95},
    {"BRYCE", 96},      {"BRYNLEE", 97},    {"BRYSON", 98},
    {"CADEN", 99},      {"CALEB", 100},     {"CALLIE", 101},
    {"CALVIN", 102},    {"CAMDEN", 103},    {"CAMERON", 104},
    {"CAMILA", 105},    {"CARLOS", 106},    {"CAROLINE", 107},
    {"CARSON", 108},    {"CARTER", 109},    {"CATHERINE", 110},
    {"CAYDEN", 111},    {"CECILIA", 112},   {"CHARLES", 113},
    {"CHARLIE", 114},   {"CHARLOTTE", 115}, {"CHASE", 116},
    {"CHLOE", 117},     {"CHRISTIAN", 118}, {"CHRISTOPHER", 119},
    {"CLAIRE", 120},    {"CLARA", 121},     {"CLAYTON", 122},
    {"COLE", 123},      {"COLIN", 124},     {"COLTON", 125},
    {"CONNOR", 126},    {"COOPER", 127},    {"CORA", 128},
    {"DAISY", 129},     {"DAKOTA", 130},    {"DALEYZA", 131},
    {"DAMIAN", 132},    {"DANIEL", 133},    {"DANIELA", 134},
    {"DAVID", 135},     {"DAWSON", 136},    {"DEAN", 137},
    {"DECLAN", 138},    {"DELANEY", 139},   {"DELILAH", 140},
    {"DEREK", 141},     {"DESTINY", 142},   {"DIANA", 143},
    {"DIEGO", 144},     {"DOMINIC", 145},   {"DYLAN", 146},
    {"EASTON", 147},    {"EDEN", 148},      {"EDWARD", 149},
    {"ELEANOR", 150},   {"ELENA", 151},     {"ELI", 152},
    {"ELIANA", 153},    {"ELIAS", 154},     {"ELIJAH", 155},
    {"ELISE", 156},     {"ELIZA", 157},     {"ELIZABETH", 158},
    {"ELLA", 159},      {"ELLIANA", 160},   {"ELLIE", 161},
    {"ELLIOT", 162},    {"ELLIOTT", 163},   {"ELOISE", 164},
    {"EMERSON", 165},   {"EMERSYN", 166},   {"EMERY", 167},
    {"EMILIA", 168},    {"EMILIANO", 169},  {"EMILY", 170},
    {"EMMA", 171},      {"EMMANUEL", 172},  {"EMMETT", 173},
    {"ERIC", 174},      {"ESTHER", 175},    {"ETHAN", 176},
    {"EVA", 177},       {"EVAN", 178},      {"EVELYN", 179},
    {"EVERETT", 180},   {"EVERLY", 181},    {"EZEKIEL", 182},
    {"EZRA", 183},      {"FAITH", 184},     {"FELIX", 185},
    {"FINLEY", 186},    {"FINN", 187},      {"FIONA", 188},
    {"GABRIEL", 189},   {"GABRIELLA", 190}, {"GAEL", 191},
    {"GAVIN", 192},     {"GENESIS", 193},   {"GENEVIEVE", 194},
    {"GEORGE", 195},    {"GEORGIA", 196},   {"GIANNA", 197},
    {"GIOVANNI", 198},  {"GRACE", 199},     {"GRACIE", 200},
    {"GRAHAM", 201},    {"GRANT", 202},     {"GRAYSON", 203},
    {"GREYSON", 204},   {"GRIFFIN", 205},   {"HADLEY", 206},
    {"HAILEY", 207},    {"HANNAH", 208},    {"HARLEY", 209},
    {"HARMONY", 210},   {"HARPER", 211},    {"HARRISON", 212},
    {"HAYDEN", 213},    {"HAZEL", 214},     {"HENRY", 215},
    {"HOLDEN", 216},    {"HUDSON", 217},    {"HUNTER", 218},
    {"IAN", 219},       {"IRIS", 220},      {"ISAAC", 221},
    {"ISABEL", 222},    {"ISABELLA", 223},  {"ISABELLE", 224},
    {"ISAIAH", 225},    {"ISLA", 226},      {"ISRAEL", 227},
    {"IVAN", 228},      {"IVY", 229},       {"JACE", 230},
    {"JACK", 231},      {"JACKSON", 232},   {"JACOB", 233},
    {"JADE", 234},      {"JADEN", 235},     {"JAKE", 236},
    {"JAMES", 237},     {"JAMESON", 238},   {"JASMINE", 239},
    {"JASON", 240},     {"JASPER", 241},    {"JAVIER", 242},
    {"JAX", 243},       {"JAXON", 244},     {"JAXSON", 245},
    {"JAYCE", 246},     {"JAYDEN", 247},    {"JAYLA", 248},
    {"JEREMIAH", 249},  {"JEREMY", 250},    {"JESSE", 251},
    {"JESSICA", 252},   {"JESUS", 253},     {"JOANNA", 254},
    {"JOCELYN", 255},   {"JOEL", 256},      {"JOHN", 257},
    {"JONAH", 258},     {"JONATHAN", 259},  {"JORDAN", 260},
    {"JORDYN", 261},    {"JORGE", 262},     {"JOSE", 263},
    {"JOSEPH", 264},    {"JOSEPHINE", 265}, {"JOSHUA", 266},
    {"JOSIAH", 267},    {"JOSIE", 268},     {"JOSUE", 269},
    {"JUAN", 270},      {"JUDAH", 271},     {"JUDE", 272},
    {"JULIA", 273},     {"JULIAN", 274},    {"JULIANA", 275},
    {"JULIANNA", 276},  {"JULIET", 277},    {"JULIETTE", 278},
    {"JUNE", 279},      {"JUSTIN", 280},    {"KADEN", 281},
    {"KAI", 282},       {"KAIDEN", 283},    {"KALEB", 284},
    {"KARTER", 285},    {"KATHERINE", 286}, {"KAYDEN", 287},
    {"KAYLA", 288},     {"KAYLEE", 289},    {"KENDALL", 290},
    {"KENNEDY", 291},   {"KENNETH", 292},   {"KEVIN", 293},
    {"KHLOE", 294},     {"KILLIAN", 295},   {"KIMBERLY", 296},
    {"KING", 297},      {"KINGSTON", 298},  {"KINSLEY", 299},
    {"KNOX", 300},      {"KYLE", 301},      {"KYLIE", 302},
    {"KYRIE", 303},     {"LAILA", 304},     {"LANDON", 305},
    {"LAUREN", 306},    {"LAYLA", 307},     {"LEAH", 308},
    {"LEILA", 309},     {"LEILANI", 310},   {"LEO", 311},
    {"LEON", 312},      {"LEONARDO", 313},  {"LEVI", 314},
    {"LIAM", 315},      {"LILA", 316},      {"LILIANA", 317},
    {"LILLIAN", 318},   {"LILLY", 319},     {"LILY", 320},
    {"LINCOLN", 321},   {"LOGAN", 322},     {"LOLA", 323},
    {"LONDON", 324},    {"LONDYN", 325},    {"LORENZO", 326},
    {"LUCA", 327},      {"LUCAS", 328},     {"LUCIA", 329},
    {"LUCY", 330},      {"LUIS", 331},      {"LUKAS", 332},
    {"LUKE", 333},      {"LUNA", 334},      {"LYDIA", 335},
    {"LYLA", 336},      {"MACKENZIE", 337}, {"MADDOX", 338},
    {"MADELINE", 339},  {"MADELYN", 340},   {"MADISON", 341},
    {"MAGGIE", 342},    {"MAKAYLA", 343},   {"MALACHI", 344},
    {"MALIA", 345},     {"MARCUS", 346},    {"MARGARET", 347},
    {"MARIA", 348},     {"MARIAH", 349},    {"MARK", 350},
    {"MARLEY", 351},    {"MARY", 352},      {"MASON", 353},
    {"MATEO", 354},     {"MATIAS", 355},    {"MATTEO", 356},
    {"MATTHEW", 357},   {"MAVERICK", 358},  {"MAX", 359},
    {"MAXIMUS", 360},   {"MAXWELL", 361},   {"MAYA", 362},
    {"MCKENZIE", 363},  {"MELANIE", 364},   {"MELODY", 365},
    {"MESSIAH", 366},   {"MIA", 367},       {"MICAH", 368},
    {"MICHAEL", 369},   {"MICHELLE", 370},  {"MIGUEL", 371},
    {"MILA", 372},      {"MILES", 373},     {"MILO", 374},
    {"MOLLY", 375},     {"MORGAN", 376},    {"MYA", 377},
    {"MYLES", 378},     {"NAOMI", 379},     {"NATALIA", 380},
    {"NATALIE", 381},   {"NATHAN", 382},    {"NATHANIEL", 383},
    {"NEVAEH", 384},    {"NICHOLAS", 385},  {"NICOLAS", 386},
    {"NICOLE", 387},    {"NOAH", 388},      {"NOELLE", 389},
    {"NOLAN", 390},     {"NORA", 391},      {"NORAH", 392},
    {"NOVA", 393},      {"OLIVER", 394},    {"OLIVIA", 395},
    {"OMAR", 396},      {"OSCAR", 397},     {"OWEN", 398},
    {"PAIGE", 399},     {"PAISLEY", 400},   {"PARKER", 401},
    {"PATRICK", 402},   {"PAUL", 403},      {"PAXTON", 404},
    {"PAYTON", 405},    {"PENELOPE", 406},  {"PETER", 407},
    {"PEYTON", 408},    {"PIPER", 409},     {"PRESLEY", 410},
    {"PRESTON", 411},   {"QUINN", 412},     {"RACHEL", 413},
    {"RAELYNN", 414},   {"REAGAN", 415},    {"REBECCA", 416},
    {"REESE", 417},     {"REMI", 418},      {"REMINGTON", 419},
    {"RHETT", 420},     {"RICHARD", 421},   {"RILEY", 422},
    {"RIVER", 423},     {"ROBERT", 424},    {"ROMAN", 425},
    {"ROSALIE", 426},   {"ROSE", 427},      {"ROWAN", 428},
    {"RUBY", 429},      {"RYAN", 430},      {"RYDER", 431},
    {"RYKER", 432},     {"RYLEE", 433},     {"RYLEIGH", 434},
    {"SADIE", 435},     {"SAMANTHA", 436},  {"SAMUEL", 437},
    {"SANTIAGO", 438},  {"SARA", 439},      {"SARAH", 440},
    {"SAVANNAH", 441},  {"SAWYER", 442},    {"SCARLETT", 443},
    {"SEBASTIAN", 444}, {"SELENA", 445},    {"SERENITY", 446},
    {"SIENNA", 447},    {"SILAS", 448},     {"SKYLAR", 449},
    {"SLOANE", 450},    {"SOFIA", 451},     {"SOPHIA", 452},
    {"SOPHIE", 453},    {"STELLA", 454},    {"STEVEN", 455},
    {"SUMMER", 456},    {"SYDNEY", 457},    {"TAYLOR", 458},
    {"TEAGAN", 459},    {"TESSA", 460},     {"THEODORE", 461},
    {"THIAGO", 462},    {"THOMAS", 463},    {"TIMOTHY", 464},
    {"TRINITY", 465},   {"TRISTAN", 466},   {"TUCKER", 467},
    {"TYLER", 468},     {"VALENTINA", 469}, {"VALERIA", 470},
    {"VALERIE", 471},   {"VANESSA", 472},   {"VICTOR", 473},
    {"VICTORIA", 474},  {"VINCENT", 475},   {"VIOLET", 476},
    {"VIVIAN", 477},    {"WAYLON", 478},    {"WESLEY", 479},
    {"WESTON", 480},    {"WILLIAM", 481},   {"WILLOW", 482},
    {"WYATT", 483},     {"XANDER", 484},    {"XAVIER", 485},
    {"XIMENA", 486},    {"ZACHARY", 487},   {"ZANDER", 488},
    {"ZANE", 489},      {"ZAYDEN", 490},    {"ZION", 491},
    {"ZOE", 492},       {"ZOEY", 493}};

unordered_map<string, int> lastNamesNumberedMap = {
    {"ACOSTA", 0},       {"ADAMS", 1},        {"ADKINS", 2},
    {"AGUILAR", 3},      {"AGUIRRE", 4},      {"ALEXANDER", 5},
    {"ALLEN", 6},        {"ALVARADO", 7},     {"ALVAREZ", 8},
    {"ANDERSON", 9},     {"ANDREWS", 10},     {"ARMSTRONG", 11},
    {"ARNOLD", 12},      {"AUSTIN", 13},      {"AVILA", 14},
    {"AYALA", 15},       {"BAILEY", 16},      {"BAKER", 17},
    {"BALDWIN", 18},     {"BANKS", 19},       {"BARBER", 20},
    {"BARKER", 21},      {"BARNES", 22},      {"BARNETT", 23},
    {"BARRETT", 24},     {"BARTON", 25},      {"BATES", 26},
    {"BECK", 27},        {"BECKER", 28},      {"BELL", 29},
    {"BENNETT", 30},     {"BENSON", 31},      {"BERRY", 32},
    {"BISHOP", 33},      {"BLACK", 34},       {"BLAIR", 35},
    {"BLAKE", 36},       {"BOWEN", 37},       {"BOWMAN", 38},
    {"BOYD", 39},        {"BRADLEY", 40},     {"BRADY", 41},
    {"BREWER", 42},      {"BROOKS", 43},      {"BROWN", 44},
    {"BRYANT", 45},      {"BURGESS", 46},     {"BURKE", 47},
    {"BURNS", 48},       {"BURTON", 49},      {"BUSH", 50},
    {"BUTLER", 51},      {"BYRD", 52},        {"CABRERA", 53},
    {"CALDERON", 54},    {"CALDWELL", 55},    {"CAMACHO", 56},
    {"CAMPBELL", 57},    {"CAMPOS", 58},      {"CANNON", 59},
    {"CARDENAS", 60},    {"CARLSON", 61},     {"CARPENTER", 62},
    {"CARR", 63},        {"CARRILLO", 64},    {"CARROLL", 65},
    {"CARTER", 66},      {"CASTANEDA", 67},   {"CASTILLO", 68},
    {"CASTRO", 69},      {"CERVANTES", 70},   {"CHAMBERS", 71},
    {"CHAN", 72},        {"CHANDLER", 73},    {"CHANG", 74},
    {"CHAPMAN", 75},     {"CHAVEZ", 76},      {"CHEN", 77},
    {"CHRISTENSEN", 78}, {"CLARK", 79},       {"CLARKE", 80},
    {"COHEN", 81},       {"COLE", 82},        {"COLEMAN", 83},
    {"COLLINS", 84},     {"COLON", 85},       {"CONTRERAS", 86},
    {"COOK", 87},        {"COOPER", 88},      {"CORTEZ", 89},
    {"COX", 90},         {"CRAIG", 91},       {"CRAWFORD", 92},
    {"CROSS", 93},       {"CRUZ", 94},        {"CUMMINGS", 95},
    {"CUNNINGHAM", 96},  {"CURRY", 97},       {"CURTIS", 98},
    {"DANIEL", 99},      {"DANIELS", 100},    {"DAVIDSON", 101},
    {"DAVIS", 102},      {"DAWSON", 103},     {"DAY", 104},
    {"DEAN", 105},       {"DELACRUZ", 106},   {"DELEON", 107},
    {"DELGADO", 108},    {"DENNIS", 109},     {"DIAZ", 110},
    {"DIXON", 111},      {"DOMINGUEZ", 112},  {"DOUGLAS", 113},
    {"DOYLE", 114},      {"DUNCAN", 115},     {"DUNN", 116},
    {"DURAN", 117},      {"EDWARDS", 118},    {"ELLIOTT", 119},
    {"ELLIS", 120},      {"ERICKSON", 121},   {"ESPINOZA", 122},
    {"ESTRADA", 123},    {"EVANS", 124},      {"FARMER", 125},
    {"FERGUSON", 126},   {"FERNANDEZ", 127},  {"FIELDS", 128},
    {"FIGUEROA", 129},   {"FISCHER", 130},    {"FISHER", 131},
    {"FITZGERALD", 132}, {"FLEMING", 133},    {"FLETCHER", 134},
    {"FLORES", 135},     {"FORD", 136},       {"FOSTER", 137},
    {"FOWLER", 138},     {"FOX", 139},        {"FRANCIS", 140},
    {"FRANCO", 141},     {"FRANK", 142},      {"FRANKLIN", 143},
    {"FRAZIER", 144},    {"FREEMAN", 145},    {"FUENTES", 146},
    {"FULLER", 147},     {"GALLAGHER", 148},  {"GALLEGOS", 149},
    {"GARCIA", 150},     {"GARDNER", 151},    {"GARNER", 152},
    {"GARRETT", 153},    {"GARZA", 154},      {"GEORGE", 155},
    {"GIBSON", 156},     {"GILBERT", 157},    {"GILL", 158},
    {"GOMEZ", 159},      {"GONZALES", 160},   {"GONZALEZ", 161},
    {"GOODMAN", 162},    {"GOODWIN", 163},    {"GORDON", 164},
    {"GRAHAM", 165},     {"GRANT", 166},      {"GRAVES", 167},
    {"GRAY", 168},       {"GREEN", 169},      {"GREENE", 170},
    {"GREGORY", 171},    {"GRIFFIN", 172},    {"GRIFFITH", 173},
    {"GROSS", 174},      {"GUERRA", 175},     {"GUERRERO", 176},
    {"GUTIERREZ", 177},  {"GUZMAN", 178},     {"HAIL", 179},
    {"HALE", 180},       {"HALL", 181},       {"HAMILTON", 182},
    {"HAMMOND", 183},    {"HAMPTON", 184},    {"HANSEN", 185},
    {"HANSON", 186},     {"HARDY", 187},      {"HARMON", 188},
    {"HARPER", 189},     {"HARRINGTON", 190}, {"HARRIS", 191},
    {"HARRISON", 192},   {"HART", 193},       {"HARVEY", 194},
    {"HAWKINS", 195},    {"HAYES", 196},      {"HAYNES", 197},
    {"HENDERSON", 198},  {"HENRY", 199},      {"HERNANDEZ", 200},
    {"HERRERA", 201},    {"HICKS", 202},      {"HIGGINS", 203},
    {"HILL", 204},       {"HINES", 205},      {"HODGES", 206},
    {"HOFFMAN", 207},    {"HOLLAND", 208},    {"HOLMES", 209},
    {"HOLT", 210},       {"HOPKINS", 211},    {"HORTON", 212},
    {"HOWARD", 213},     {"HOWELL", 214},     {"HUANG", 215},
    {"HUBBARD", 216},    {"HUDSON", 217},     {"HUGHES", 218},
    {"HUNT", 219},       {"HUNTER", 220},     {"INGRAM", 221},
    {"JACKSON", 222},    {"JACOBS", 223},     {"JAMES", 224},
    {"JENKINS", 225},    {"JENNINGS", 226},   {"JENSEN", 227},
    {"JIMENEZ", 228},    {"JOHNSON", 229},    {"JOHNSTON", 230},
    {"JONES", 231},      {"JORDAN", 232},     {"JOSEPH", 233},
    {"JUAREZ", 234},     {"KELLER", 235},     {"KELLEY", 236},
    {"KELLY", 237},      {"KENNEDY", 238},    {"KHAN", 239},
    {"KIM", 240},        {"KING", 241},       {"KLEIN", 242},
    {"KNIGHT", 243},     {"LAMBERT", 244},    {"LANE", 245},
    {"LARA", 246},       {"LARSON", 247},     {"LAWRENCE", 248},
    {"LAWSON", 249},     {"LE", 250},         {"LEE", 251},
    {"LEON", 252},       {"LEONARD", 253},    {"LEWIS", 254},
    {"LI", 255},         {"LIN", 256},        {"LITTLE", 257},
    {"LIU", 258},        {"LOGAN", 259},      {"LONG", 260},
    {"LOPEZ", 261},      {"LOVE", 262},       {"LOWE", 263},
    {"LUCAS", 264},      {"LUNA", 265},       {"LYNCH", 266},
    {"LYONS", 267},      {"MACK", 268},       {"MALDONADO", 269},
    {"MALONE", 270},     {"MANN", 271},       {"MANNING", 272},
    {"MARQUEZ", 273},    {"MARSHALL", 274},   {"MARTIN", 275},
    {"MARTINEZ", 276},   {"MASON", 277},      {"MATTHEWS", 278},
    {"MAXWELL", 279},    {"MAY", 280},        {"MCCARTHY", 281},
    {"MCCOY", 282},      {"MCDANIEL", 283},   {"MCDONALD", 284},
    {"MCGEE", 285},      {"MCKINNEY", 286},   {"MCLAUGHLIN", 287},
    {"MEDINA", 288},     {"MEJIA", 289},      {"MENDEZ", 290},
    {"MENDOZA", 291},    {"MEYER", 292},      {"MILES", 293},
    {"MILLER", 294},     {"MILLS", 295},      {"MIRANDA", 296},
    {"MITCHELL", 297},   {"MOLINA", 298},     {"MONTGOMERY", 299},
    {"MONTOYA", 300},    {"MOORE", 301},      {"MORALES", 302},
    {"MORAN", 303},      {"MORENO", 304},     {"MORGAN", 305},
    {"MORRIS", 306},     {"MORRISON", 307},   {"MOSS", 308},
    {"MULLINS", 309},    {"MUNOZ", 310},      {"MURPHY", 311},
    {"MURRAY", 312},     {"MYERS", 313},      {"NAVARRO", 314},
    {"NEAL", 315},       {"NELSON", 316},     {"NEWMAN", 317},
    {"NEWTON", 318},     {"NGUYEN", 319},     {"NICHOLS", 320},
    {"NORMAN", 321},     {"NORRIS", 322},     {"NUNEZ", 323},
    {"OBRIEN", 324},     {"OCHOA", 325},      {"OCONNOR", 326},
    {"OLIVER", 327},     {"OLSON", 328},      {"ORTEGA", 329},
    {"ORTIZ", 330},      {"OWENS", 331},      {"PACHECO", 332},
    {"PADILLA", 333},    {"PAGE", 334},       {"PALMER", 335},
    {"PARK", 336},       {"PARKER", 337},     {"PARKS", 338},
    {"PARSONS", 339},    {"PATEL", 340},      {"PATTERSON", 341},
    {"PAUL", 342},       {"PAYNE", 343},      {"PEARSON", 344},
    {"PENA", 345},       {"PEREZ", 346},      {"PERKINS", 347},
    {"PERRY", 348},      {"PERSON", 349},     {"PETERS", 350},
    {"PETERSON", 351},   {"PHAM", 352},       {"PHILLIPS", 353},
    {"PIERCE", 354},     {"PORTER", 355},     {"POTTER", 356},
    {"POWELL", 357},     {"POWERS", 358},     {"PRICE", 359},
    {"QUINN", 360},      {"RAMIREZ", 361},    {"RAMOS", 362},
    {"RAMSEY", 363},     {"RAY", 364},        {"REED", 365},
    {"REESE", 366},      {"REEVES", 367},     {"REID", 368},
    {"REYES", 369},      {"REYNOLDS", 370},   {"RHODES", 371},
    {"RICE", 372},       {"RICHARDS", 373},   {"RICHARDSON", 374},
    {"RILEY", 375},      {"RIOS", 376},       {"RIVAS", 377},
    {"RIVERA", 378},     {"ROBBINS", 379},    {"ROBERTS", 380},
    {"ROBERTSON", 381},  {"ROBINSON", 382},   {"ROBLES", 383},
    {"RODGERS", 384},    {"RODRIGUEZ", 385},  {"ROGERS", 386},
    {"ROJAS", 387},      {"ROMAN", 388},      {"ROMERO", 389},
    {"ROSALES", 390},    {"ROSE", 391},       {"ROSS", 392},
    {"ROWE", 393},       {"RUIZ", 394},       {"RUSSELL", 395},
    {"RYAN", 396},       {"SALAZAR", 397},    {"SALINAS", 398},
    {"SANCHEZ", 399},    {"SANDERS", 400},    {"SANDOVAL", 401},
    {"SANTIAGO", 402},   {"SANTOS", 403},     {"SAUNDERS", 404},
    {"SCHMIDT", 405},    {"SCHNEIDER", 406},  {"SCHROEDER", 407},
    {"SCHULTZ", 408},    {"SCHWARTZ", 409},   {"SCOTT", 410},
    {"SERRANO", 411},    {"SHARP", 412},      {"SHAW", 413},
    {"SHELTON", 414},    {"SHERMAN", 415},    {"SILVA", 416},
    {"SIMMONS", 417},    {"SIMON", 418},      {"SIMPSON", 419},
    {"SIMS", 420},       {"SINGH", 421},      {"SMITH", 422},
    {"SNYDER", 423},     {"SOLIS", 424},      {"SOTO", 425},
    {"SPENCER", 426},    {"STANLEY", 427},    {"STEELE", 428},
    {"STEPHENS", 429},   {"STEVENS", 430},    {"STEVENSON", 431},
    {"STEWART", 432},    {"STONE", 433},      {"STRICKLAND", 434},
    {"SULLIVAN", 435},   {"SUTTON", 436},     {"SWANSON", 437},
    {"TATE", 438},       {"TAYLOR", 439},     {"TERRY", 440},
    {"THOMAS", 441},     {"THOMPSON", 442},   {"THORNTON", 443},
    {"TODD", 444},       {"TORRES", 445},     {"TOWNSEND", 446},
    {"TRAN", 447},       {"TRUJILLO", 448},   {"TUCKER", 449},
    {"TURNER", 450},     {"VALDEZ", 451},     {"VALENCIA", 452},
    {"VARGAS", 453},     {"VASQUEZ", 454},    {"VAUGHN", 455},
    {"VAZQUEZ", 456},    {"VEGA", 457},       {"VELASQUEZ", 458},
    {"WADE", 459},       {"WAGNER", 460},     {"WALKER", 461},
    {"WALLACE", 462},    {"WALSH", 463},      {"WALTERS", 464},
    {"WALTON", 465},     {"WANG", 466},       {"WARD", 467},
    {"WARNER", 468},     {"WARREN", 469},     {"WASHINGTON", 470},
    {"WATERS", 471},     {"WATKINS", 472},    {"WATSON", 473},
    {"WATTS", 474},      {"WEAVER", 475},     {"WEBB", 476},
    {"WEBER", 477},      {"WEBSTER", 478},    {"WELCH", 479},
    {"WELLS", 480},      {"WEST", 481},       {"WHEELER", 482},
    {"WHITE", 483},      {"WILLIAMS", 484},   {"WILLIAMSON", 485},
    {"WILLIS", 486},     {"WILSON", 487},     {"WISE", 488},
    {"WOLF", 489},       {"WOLFE", 490},      {"WONG", 491},
    {"WOOD", 492},       {"WOODS", 493},      {"WRIGHT", 494},
    {"WU", 495},         {"YANG", 496},       {"YOUNG", 497},
    {"ZHANG", 498},      {"ZIMMERMAN", 499}};

long power10[10] = {1,      10,      100,      1000,      10000,
                    100000, 1000000, 10000000, 100000000, 100000000};

struct myData {
  Data *d;
  int firstNameOrder;
  int lastNameOrder;
  long ssnOrder;
};

const int RadixShift = 32;
const int RadixShiftPower = 5;
const int STDSORT_CUTOFF = 20;

enum field {
  lastName = 1,
  firstName = 2,
  ssn = 3,
};

int valueAt(myData *d, int pos, field type) {
  int shift = pos * RadixShiftPower;
  if (type == field::firstName) {
    return (d->firstNameOrder >> shift) % RadixShift;
  }
  if (type == field::lastName) {
    return (d->lastNameOrder >> shift) % RadixShift;
  }
  return (d->ssnOrder >> shift) % RadixShift;
}

void _afsSwapAll(myData **&v, int *offsets, int start, int digit, field type) {
  int i = start;
  int nf[RadixShift] = {};
  int current_block = 0;
  copy(offsets, offsets + RadixShift, begin(nf));
  while (current_block < RadixShift - 1) {
    if (i >= start + offsets[current_block + 1]) {
      current_block += 1;
      continue;
    }
    int val = valueAt(v[i], digit, type);
    if (val == current_block) {
      i += 1;
      continue;
    }
    auto swap_to = start + nf[val];
    auto tmp = v[swap_to];
    v[swap_to] = v[i];
    v[i] = tmp;
    nf[val] += 1;
  }
}

void _afsOffsets(myData **&v, int start, int end, int digit, int *offsets,
                 field type) {
  int counts[RadixShift] = {};
  for (int i = start; i < end; i++) {
    counts[valueAt(v[i], digit, type)] += 1;
  }
  int sum = 0;
  for (int i = 0; i < RadixShift; i++) {
    offsets[i] = sum;
    sum += counts[i];
  }
}

void _recurseRadix(myData **&v, int start, int end, int digit, int max,
                   field type) {
  if (start + 1 >= end) {
    return;
  }
  if (end - start < STDSORT_CUTOFF) {
    if (start + 1 >= end) {
      return;
    }
    auto b = v + start;
    auto l = v + end;
    if (type == field::lastName) {
      sort(b, l, [](myData *first, myData *last) {
        return first->lastNameOrder < last->lastNameOrder;
      });
    } else if (type == field::firstName) {
      sort(b, l, [](myData *first, myData *last) {
        return first->firstNameOrder < last->firstNameOrder;
      });
    } else {
      sort(b, l, [](myData *first, myData *last) {
        return first->ssnOrder < last->ssnOrder;
      });
    }
    return;
  }
  int offsets[RadixShift + 1] = {};
  offsets[RadixShift] = end - start;
  _afsOffsets(v, start, end, digit, offsets, type);
  _afsSwapAll(v, offsets, start, digit, type);
  if (digit == 0) {
    return;
  }
  for (int i = 0; i < RadixShift; i++) {
    _recurseRadix(v, start + offsets[i], start + offsets[i + 1], digit - 1, max,
                  type);
  }
}

int max_digit(field type) {
  if (type == field::ssn) {
    return 5;
  }
  return 2;
}

void RadixSort(myData **v, int start, int end, field type) {
  int md = max_digit(type);
  _recurseRadix(v, start, end, md, md, type);
}

myData *vec[1001000];

void sortDataList(list<Data *> &l) {
  // Fill this in

  if (l.front()->lastName == l.back()->lastName) {
    int size = l.size();

    int i = 0;
    for (auto it = l.begin(); it != l.end(); it++) {
      auto a = *it;
      const char *ssn = a->ssn.c_str();
      vec[i++] = new myData{
          a,
          firstNamesOrdered[a->firstName],
          lastNamesNumberedMap[a->lastName],
          power10[8] * (ssn[0] - '0') + power10[7] * (ssn[1] - '0') +
              power10[6] * (ssn[2] - '0') + power10[5] * (ssn[4] - '0') +
              power10[4] * (ssn[5] - '0') + power10[3] * (ssn[7] - '0') +
              power10[2] * (ssn[8] - '0') + power10[1] * (ssn[9] - '0') +
              (ssn[10] - '0'),
      };
    }

    RadixSort(vec, 0, size, field::lastName);
    list<int> offsetsLists = {0};
    for (int i = 1; i < size; i++) {
      if (vec[i]->lastNameOrder == vec[i - 1]->lastNameOrder) {
        continue;
      }
      offsetsLists.push_back(i);
    }
    offsetsLists.push_back(size);

    for (auto it = next(offsetsLists.begin()); it != offsetsLists.end(); it++) {
      auto p = prev(it);
      RadixSort(vec, *p, *it, field::firstName);
    }

    list<int> offsetsLists1 = {0};
    for (int i = 1; i < size; i++) {
      if (vec[i]->firstNameOrder == vec[i - 1]->firstNameOrder &&
          vec[i]->lastNameOrder == vec[i - 1]->lastNameOrder) {
        continue;
      }
      offsetsLists1.push_back(i);
    }
    offsetsLists1.push_back(size);

    for (auto it = next(offsetsLists1.begin()); it != offsetsLists1.end();
         it++) {
      RadixSort(vec, *prev(it), *it, field::ssn);
    }

    l.clear();
    for (int i = 0; i < size; i++)
      l.push_back(vec[i]->d);
    return;
  }

  for (auto it = l.begin(); it != l.end(); ++it) {
    firstNamesNumberedMap[(*it)->firstName].push_back(*it);
  }

  for (auto it = 0; it < 500; ++it) {
    auto pointer = firstNamesNumberedMap[firstNamesString[it]];
    for (auto it2 = pointer.begin(); it2 != pointer.end(); ++it2) {
      secondNamesMap[(*it2)->lastName].push_back(*it2);
    }
  }

  auto listIt = l.begin();
  for (int j = 0; j < 500; ++j) {
    auto pointer = secondNamesMap[lastNamesString[j]];
    int k = pointer.size() - 1;
    for (int i = 0; i <= k; ++i) {
      if (i != k && pointer[i]->firstName == pointer[i + 1]->firstName) {
        Data *xspt[500];
        int pos = 0;
        int z = i;
        xspt[pos] = pointer[i];
        ++pos;
        ++i;
        xspt[pos] = pointer[i];
        ++pos;
        while (i < k && pointer[i + 1]->firstName == pointer[z]->firstName) {
          ++i;
          xspt[pos] = pointer[i];
          pos++;
        }
        sort(xspt, &xspt[pos], [](const Data *person1, const Data *person2) {
          if (person1->ssn >= person2->ssn)
            return false;
          else
            return true;
        });
        for (int gg = 0; gg < pos; gg++) {
          *listIt = xspt[gg];
          ++listIt;
        }
      } else {
        *listIt = pointer[i];
        ++listIt;
      }
    }
  }
}

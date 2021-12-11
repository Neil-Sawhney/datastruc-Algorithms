// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2021

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

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
    for (auto pData:l) {
        output << pData->lastName << " "
               << pData->firstName << " "
               << pData->ssn << "\n";
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
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

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

map< string, vector<Data *>> firstMap = {{"AALIYAH", vector<Data *>()},{"AARON", vector<Data *>()},{"ABEL", vector<Data *>()},{"ABIGAIL", vector<Data *>()},{"ABRAHAM", vector<Data *>()},{"ADALINE", vector<Data *>()},{"ADALYN", vector<Data *>()},{"ADALYNN", vector<Data *>()},{"ADAM", vector<Data *>()},{"ADDISON", vector<Data *>()},{"ADELINE", vector<Data *>()},{"ADELYN", vector<Data *>()},{"ADRIAN", vector<Data *>()},{"ADRIANA", vector<Data *>()},{"AIDAN", vector<Data *>()},{"AIDEN", vector<Data *>()},{"ALAINA", vector<Data *>()},{"ALAN", vector<Data *>()},{"ALANA", vector<Data *>()},{"ALAYNA", vector<Data *>()},{"ALEJANDRO", vector<Data *>()},{"ALEX", vector<Data *>()},{"ALEXA", vector<Data *>()},{"ALEXANDER", vector<Data *>()},{"ALEXANDRA", vector<Data *>()},{"ALEXIS", vector<Data *>()},{"ALICE", vector<Data *>()},{"ALINA", vector<Data *>()},{"ALIVIA", vector<Data *>()},{"ALIYAH", vector<Data *>()},{"ALLISON", vector<Data *>()},{"ALYSSA", vector<Data *>()},{"AMARA", vector<Data *>()},{"AMAYA", vector<Data *>()},{"AMELIA", vector<Data *>()},{"AMIR", vector<Data *>()},{"AMY", vector<Data *>()},{"ANA", vector<Data *>()},{"ANASTASIA", vector<Data *>()},{"ANDREA", vector<Data *>()},{"ANDRES", vector<Data *>()},{"ANDREW", vector<Data *>()},{"ANGEL", vector<Data *>()},{"ANGELA", vector<Data *>()},{"ANGELINA", vector<Data *>()},{"ANNA", vector<Data *>()},{"ANNABELLE", vector<Data *>()},{"ANTHONY", vector<Data *>()},{"ANTONIO", vector<Data *>()},{"ARABELLA", vector<Data *>()},{"ARIA", vector<Data *>()},{"ARIANA", vector<Data *>()},{"ARIANNA", vector<Data *>()},{"ARIEL", vector<Data *>()},{"ARTHUR", vector<Data *>()},{"ARYA", vector<Data *>()},{"ASHER", vector<Data *>()},{"ASHLEY", vector<Data *>()},{"ASHTON", vector<Data *>()},{"ATHENA", vector<Data *>()},{"AUBREE", vector<Data *>()},{"AUBREY", vector<Data *>()},{"AUDREY", vector<Data *>()},{"AUGUST", vector<Data *>()},{"AURORA", vector<Data *>()},{"AUSTIN", vector<Data *>()},{"AUTUMN", vector<Data *>()},{"AVA", vector<Data *>()},{"AVERY", vector<Data *>()},{"AVERY", vector<Data *>()},{"AXEL", vector<Data *>()},{"AYDEN", vector<Data *>()},{"AYLA", vector<Data *>()},{"BAILEY", vector<Data *>()},{"BARRETT", vector<Data *>()},{"BEAU", vector<Data *>()},{"BECKETT", vector<Data *>()},{"BELLA", vector<Data *>()},{"BENJAMIN", vector<Data *>()},{"BENNETT", vector<Data *>()},{"BENTLEY", vector<Data *>()},{"BLAKE", vector<Data *>()},{"BRADLEY", vector<Data *>()},{"BRADY", vector<Data *>()},{"BRANDON", vector<Data *>()},{"BRANTLEY", vector<Data *>()},{"BRAXTON", vector<Data *>()},{"BRAYDEN", vector<Data *>()},{"BRIAN", vector<Data *>()},{"BRIANNA", vector<Data *>()},{"BRIELLE", vector<Data *>()},{"BRODY", vector<Data *>()},{"BROOKE", vector<Data *>()},{"BROOKLYN", vector<Data *>()},{"BROOKLYNN", vector<Data *>()},{"BROOKS", vector<Data *>()},{"BRYAN", vector<Data *>()},{"BRYCE", vector<Data *>()},{"BRYNLEE", vector<Data *>()},{"BRYSON", vector<Data *>()},{"CADEN", vector<Data *>()},{"CALEB", vector<Data *>()},{"CALLIE", vector<Data *>()},{"CALVIN", vector<Data *>()},{"CAMDEN", vector<Data *>()},{"CAMERON", vector<Data *>()},{"CAMILA", vector<Data *>()},{"CARLOS", vector<Data *>()},{"CAROLINE", vector<Data *>()},{"CARSON", vector<Data *>()},{"CARTER", vector<Data *>()},{"CATHERINE", vector<Data *>()},{"CAYDEN", vector<Data *>()},{"CECILIA", vector<Data *>()},{"CHARLES", vector<Data *>()},{"CHARLIE", vector<Data *>()},{"CHARLIE", vector<Data *>()},{"CHARLOTTE", vector<Data *>()},{"CHASE", vector<Data *>()},{"CHLOE", vector<Data *>()},{"CHRISTIAN", vector<Data *>()},{"CHRISTOPHER", vector<Data *>()},{"CLAIRE", vector<Data *>()},{"CLARA", vector<Data *>()},{"CLAYTON", vector<Data *>()},{"COLE", vector<Data *>()},{"COLIN", vector<Data *>()},{"COLTON", vector<Data *>()},{"CONNOR", vector<Data *>()},{"COOPER", vector<Data *>()},{"CORA", vector<Data *>()},{"DAISY", vector<Data *>()},{"DAKOTA", vector<Data *>()},{"DALEYZA", vector<Data *>()},{"DAMIAN", vector<Data *>()},{"DANIEL", vector<Data *>()},{"DANIELA", vector<Data *>()},{"DAVID", vector<Data *>()},{"DAWSON", vector<Data *>()},{"DEAN", vector<Data *>()},{"DECLAN", vector<Data *>()},{"DELANEY", vector<Data *>()},{"DELILAH", vector<Data *>()},{"DEREK", vector<Data *>()},{"DESTINY", vector<Data *>()},{"DIANA", vector<Data *>()},{"DIEGO", vector<Data *>()},{"DOMINIC", vector<Data *>()},{"DYLAN", vector<Data *>()},{"EASTON", vector<Data *>()},{"EDEN", vector<Data *>()},{"EDWARD", vector<Data *>()},{"ELEANOR", vector<Data *>()},{"ELENA", vector<Data *>()},{"ELI", vector<Data *>()},{"ELIANA", vector<Data *>()},{"ELIAS", vector<Data *>()},{"ELIJAH", vector<Data *>()},{"ELISE", vector<Data *>()},{"ELIZA", vector<Data *>()},{"ELIZABETH", vector<Data *>()},{"ELLA", vector<Data *>()},{"ELLIANA", vector<Data *>()},{"ELLIE", vector<Data *>()},{"ELLIOT", vector<Data *>()},{"ELLIOTT", vector<Data *>()},{"ELOISE", vector<Data *>()},{"EMERSON", vector<Data *>()},{"EMERSYN", vector<Data *>()},{"EMERY", vector<Data *>()},{"EMILIA", vector<Data *>()},{"EMILIANO", vector<Data *>()},{"EMILY", vector<Data *>()},{"EMMA", vector<Data *>()},{"EMMANUEL", vector<Data *>()},{"EMMETT", vector<Data *>()},{"ERIC", vector<Data *>()},{"ESTHER", vector<Data *>()},{"ETHAN", vector<Data *>()},{"EVA", vector<Data *>()},{"EVAN", vector<Data *>()},{"EVELYN", vector<Data *>()},{"EVERETT", vector<Data *>()},{"EVERLY", vector<Data *>()},{"EZEKIEL", vector<Data *>()},{"EZRA", vector<Data *>()},{"FAITH", vector<Data *>()},{"FELIX", vector<Data *>()},{"FINLEY", vector<Data *>()},{"FINN", vector<Data *>()},{"FIONA", vector<Data *>()},{"GABRIEL", vector<Data *>()},{"GABRIELLA", vector<Data *>()},{"GAEL", vector<Data *>()},{"GAVIN", vector<Data *>()},{"GENESIS", vector<Data *>()},{"GENEVIEVE", vector<Data *>()},{"GEORGE", vector<Data *>()},{"GEORGIA", vector<Data *>()},{"GIANNA", vector<Data *>()},{"GIOVANNI", vector<Data *>()},{"GRACE", vector<Data *>()},{"GRACIE", vector<Data *>()},{"GRAHAM", vector<Data *>()},{"GRANT", vector<Data *>()},{"GRAYSON", vector<Data *>()},{"GREYSON", vector<Data *>()},{"GRIFFIN", vector<Data *>()},{"HADLEY", vector<Data *>()},{"HAILEY", vector<Data *>()},{"HANNAH", vector<Data *>()},{"HARLEY", vector<Data *>()},{"HARMONY", vector<Data *>()},{"HARPER", vector<Data *>()},{"HARRISON", vector<Data *>()},{"HAYDEN", vector<Data *>()},{"HAYDEN", vector<Data *>()},{"HAZEL", vector<Data *>()},{"HENRY", vector<Data *>()},{"HOLDEN", vector<Data *>()},{"HUDSON", vector<Data *>()},{"HUNTER", vector<Data *>()},{"IAN", vector<Data *>()},{"IRIS", vector<Data *>()},{"ISAAC", vector<Data *>()},{"ISABEL", vector<Data *>()},{"ISABELLA", vector<Data *>()},{"ISABELLE", vector<Data *>()},{"ISAIAH", vector<Data *>()},{"ISLA", vector<Data *>()},{"ISRAEL", vector<Data *>()},{"IVAN", vector<Data *>()},{"IVY", vector<Data *>()},{"JACE", vector<Data *>()},{"JACK", vector<Data *>()},{"JACKSON", vector<Data *>()},{"JACOB", vector<Data *>()},{"JADE", vector<Data *>()},{"JADEN", vector<Data *>()},{"JAKE", vector<Data *>()},{"JAMES", vector<Data *>()},{"JAMESON", vector<Data *>()},{"JASMINE", vector<Data *>()},{"JASON", vector<Data *>()},{"JASPER", vector<Data *>()},{"JAVIER", vector<Data *>()},{"JAX", vector<Data *>()},{"JAXON", vector<Data *>()},{"JAXSON", vector<Data *>()},{"JAYCE", vector<Data *>()},{"JAYDEN", vector<Data *>()},{"JAYLA", vector<Data *>()},{"JEREMIAH", vector<Data *>()},{"JEREMY", vector<Data *>()},{"JESSE", vector<Data *>()},{"JESSICA", vector<Data *>()},{"JESUS", vector<Data *>()},{"JOANNA", vector<Data *>()},{"JOCELYN", vector<Data *>()},{"JOEL", vector<Data *>()},{"JOHN", vector<Data *>()},{"JONAH", vector<Data *>()},{"JONATHAN", vector<Data *>()},{"JORDAN", vector<Data *>()},{"JORDYN", vector<Data *>()},{"JORGE", vector<Data *>()},{"JOSE", vector<Data *>()},{"JOSEPH", vector<Data *>()},{"JOSEPHINE", vector<Data *>()},{"JOSHUA", vector<Data *>()},{"JOSIAH", vector<Data *>()},{"JOSIE", vector<Data *>()},{"JOSUE", vector<Data *>()},{"JUAN", vector<Data *>()},{"JUDAH", vector<Data *>()},{"JUDE", vector<Data *>()},{"JULIA", vector<Data *>()},{"JULIAN", vector<Data *>()},{"JULIANA", vector<Data *>()},{"JULIANNA", vector<Data *>()},{"JULIET", vector<Data *>()},{"JULIETTE", vector<Data *>()},{"JUNE", vector<Data *>()},{"JUSTIN", vector<Data *>()},{"KADEN", vector<Data *>()},{"KAI", vector<Data *>()},{"KAIDEN", vector<Data *>()},{"KALEB", vector<Data *>()},{"KARTER", vector<Data *>()},{"KATHERINE", vector<Data *>()},{"KAYDEN", vector<Data *>()},{"KAYLA", vector<Data *>()},{"KAYLEE", vector<Data *>()},{"KENDALL", vector<Data *>()},{"KENNEDY", vector<Data *>()},{"KENNETH", vector<Data *>()},{"KEVIN", vector<Data *>()},{"KHLOE", vector<Data *>()},{"KILLIAN", vector<Data *>()},{"KIMBERLY", vector<Data *>()},{"KING", vector<Data *>()},{"KINGSTON", vector<Data *>()},{"KINSLEY", vector<Data *>()},{"KNOX", vector<Data *>()},{"KYLE", vector<Data *>()},{"KYLIE", vector<Data *>()},{"KYRIE", vector<Data *>()},{"LAILA", vector<Data *>()},{"LANDON", vector<Data *>()},{"LAUREN", vector<Data *>()},{"LAYLA", vector<Data *>()},{"LEAH", vector<Data *>()},{"LEILA", vector<Data *>()},{"LEILANI", vector<Data *>()},{"LEO", vector<Data *>()},{"LEON", vector<Data *>()},{"LEONARDO", vector<Data *>()},{"LEVI", vector<Data *>()},{"LIAM", vector<Data *>()},{"LILA", vector<Data *>()},{"LILIANA", vector<Data *>()},{"LILLIAN", vector<Data *>()},{"LILLY", vector<Data *>()},{"LILY", vector<Data *>()},{"LINCOLN", vector<Data *>()},{"LOGAN", vector<Data *>()},{"LOLA", vector<Data *>()},{"LONDON", vector<Data *>()},{"LONDYN", vector<Data *>()},{"LORENZO", vector<Data *>()},{"LUCA", vector<Data *>()},{"LUCAS", vector<Data *>()},{"LUCIA", vector<Data *>()},{"LUCY", vector<Data *>()},{"LUIS", vector<Data *>()},{"LUKAS", vector<Data *>()},{"LUKE", vector<Data *>()},{"LUNA", vector<Data *>()},{"LYDIA", vector<Data *>()},{"LYLA", vector<Data *>()},{"MACKENZIE", vector<Data *>()},{"MADDOX", vector<Data *>()},{"MADELINE", vector<Data *>()},{"MADELYN", vector<Data *>()},{"MADISON", vector<Data *>()},{"MAGGIE", vector<Data *>()},{"MAKAYLA", vector<Data *>()},{"MALACHI", vector<Data *>()},{"MALIA", vector<Data *>()},{"MARCUS", vector<Data *>()},{"MARGARET", vector<Data *>()},{"MARIA", vector<Data *>()},{"MARIAH", vector<Data *>()},{"MARK", vector<Data *>()},{"MARLEY", vector<Data *>()},{"MARY", vector<Data *>()},{"MASON", vector<Data *>()},{"MATEO", vector<Data *>()},{"MATIAS", vector<Data *>()},{"MATTEO", vector<Data *>()},{"MATTHEW", vector<Data *>()},{"MAVERICK", vector<Data *>()},{"MAX", vector<Data *>()},{"MAXIMUS", vector<Data *>()},{"MAXWELL", vector<Data *>()},{"MAYA", vector<Data *>()},{"MCKENZIE", vector<Data *>()},{"MELANIE", vector<Data *>()},{"MELODY", vector<Data *>()},{"MESSIAH", vector<Data *>()},{"MIA", vector<Data *>()},{"MICAH", vector<Data *>()},{"MICHAEL", vector<Data *>()},{"MICHELLE", vector<Data *>()},{"MIGUEL", vector<Data *>()},{"MILA", vector<Data *>()},{"MILES", vector<Data *>()},{"MILO", vector<Data *>()},{"MOLLY", vector<Data *>()},{"MORGAN", vector<Data *>()},{"MYA", vector<Data *>()},{"MYLES", vector<Data *>()},{"NAOMI", vector<Data *>()},{"NATALIA", vector<Data *>()},{"NATALIE", vector<Data *>()},{"NATHAN", vector<Data *>()},{"NATHANIEL", vector<Data *>()},{"NEVAEH", vector<Data *>()},{"NICHOLAS", vector<Data *>()},{"NICOLAS", vector<Data *>()},{"NICOLE", vector<Data *>()},{"NOAH", vector<Data *>()},{"NOELLE", vector<Data *>()},{"NOLAN", vector<Data *>()},{"NORA", vector<Data *>()},{"NORAH", vector<Data *>()},{"NOVA", vector<Data *>()},{"OLIVER", vector<Data *>()},{"OLIVIA", vector<Data *>()},{"OMAR", vector<Data *>()},{"OSCAR", vector<Data *>()},{"OWEN", vector<Data *>()},{"PAIGE", vector<Data *>()},{"PAISLEY", vector<Data *>()},{"PARKER", vector<Data *>()},{"PARKER", vector<Data *>()},{"PATRICK", vector<Data *>()},{"PAUL", vector<Data *>()},{"PAXTON", vector<Data *>()},{"PAYTON", vector<Data *>()},{"PENELOPE", vector<Data *>()},{"PETER", vector<Data *>()},{"PEYTON", vector<Data *>()},{"PIPER", vector<Data *>()},{"PRESLEY", vector<Data *>()},{"PRESTON", vector<Data *>()},{"QUINN", vector<Data *>()},{"RACHEL", vector<Data *>()},{"RAELYNN", vector<Data *>()},{"REAGAN", vector<Data *>()},{"REBECCA", vector<Data *>()},{"REESE", vector<Data *>()},{"REMI", vector<Data *>()},{"REMINGTON", vector<Data *>()},{"RHETT", vector<Data *>()},{"RICHARD", vector<Data *>()},{"RILEY", vector<Data *>()},{"RIVER", vector<Data *>()},{"ROBERT", vector<Data *>()},{"ROMAN", vector<Data *>()},{"ROSALIE", vector<Data *>()},{"ROSE", vector<Data *>()},{"ROWAN", vector<Data *>()},{"ROWAN", vector<Data *>()},{"RUBY", vector<Data *>()},{"RYAN", vector<Data *>()},{"RYDER", vector<Data *>()},{"RYKER", vector<Data *>()},{"RYLEE", vector<Data *>()},{"RYLEIGH", vector<Data *>()},{"SADIE", vector<Data *>()},{"SAMANTHA", vector<Data *>()},{"SAMUEL", vector<Data *>()},{"SANTIAGO", vector<Data *>()},{"SARA", vector<Data *>()},{"SARAH", vector<Data *>()},{"SAVANNAH", vector<Data *>()},{"SAWYER", vector<Data *>()},{"SAWYER", vector<Data *>()},{"SCARLETT", vector<Data *>()},{"SEBASTIAN", vector<Data *>()},{"SELENA", vector<Data *>()},{"SERENITY", vector<Data *>()},{"SIENNA", vector<Data *>()},{"SILAS", vector<Data *>()},{"SKYLAR", vector<Data *>()},{"SLOANE", vector<Data *>()},{"SOFIA", vector<Data *>()},{"SOPHIA", vector<Data *>()},{"SOPHIE", vector<Data *>()},{"STELLA", vector<Data *>()},{"STEVEN", vector<Data *>()},{"SUMMER", vector<Data *>()},{"SYDNEY", vector<Data *>()},{"TAYLOR", vector<Data *>()},{"TEAGAN", vector<Data *>()},{"TESSA", vector<Data *>()},{"THEODORE", vector<Data *>()},{"THIAGO", vector<Data *>()},{"THOMAS", vector<Data *>()},{"TIMOTHY", vector<Data *>()},{"TRINITY", vector<Data *>()},{"TRISTAN", vector<Data *>()},{"TUCKER", vector<Data *>()},{"TYLER", vector<Data *>()},{"VALENTINA", vector<Data *>()},{"VALERIA", vector<Data *>()},{"VALERIE", vector<Data *>()},{"VANESSA", vector<Data *>()},{"VICTOR", vector<Data *>()},{"VICTORIA", vector<Data *>()},{"VINCENT", vector<Data *>()},{"VIOLET", vector<Data *>()},{"VIVIAN", vector<Data *>()},{"WAYLON", vector<Data *>()},{"WESLEY", vector<Data *>()},{"WESTON", vector<Data *>()},{"WILLIAM", vector<Data *>()},{"WILLOW", vector<Data *>()},{"WYATT", vector<Data *>()},{"XANDER", vector<Data *>()},{"XAVIER", vector<Data *>()},{"XIMENA", vector<Data *>()},{"ZACHARY", vector<Data *>()},{"ZANDER", vector<Data *>()},{"ZANE", vector<Data *>()},{"ZAYDEN", vector<Data *>()},{"ZION", vector<Data *>()},{"ZOE", vector<Data *>()},{"ZOEY", vector<Data *>()}};
map< string, vector<Data *>> lastMap = {{"ACOSTA", vector<Data *>()},{"ADAMS", vector<Data *>()},{"ADKINS", vector<Data *>()},{"AGUILAR", vector<Data *>()},{"AGUIRRE", vector<Data *>()},{"ALEXANDER", vector<Data *>()},{"ALLEN", vector<Data *>()},{"ALVARADO", vector<Data *>()},{"ALVAREZ", vector<Data *>()},{"ANDERSON", vector<Data *>()},{"ANDREWS", vector<Data *>()},{"ARMSTRONG", vector<Data *>()},{"ARNOLD", vector<Data *>()},{"AUSTIN", vector<Data *>()},{"AVILA", vector<Data *>()},{"AYALA", vector<Data *>()},{"BAILEY", vector<Data *>()},{"BAKER", vector<Data *>()},{"BALDWIN", vector<Data *>()},{"BANKS", vector<Data *>()},{"BARBER", vector<Data *>()},{"BARKER", vector<Data *>()},{"BARNES", vector<Data *>()},{"BARNETT", vector<Data *>()},{"BARRETT", vector<Data *>()},{"BARTON", vector<Data *>()},{"BATES", vector<Data *>()},{"BECK", vector<Data *>()},{"BECKER", vector<Data *>()},{"BELL", vector<Data *>()},{"BENNETT", vector<Data *>()},{"BENSON", vector<Data *>()},{"BERRY", vector<Data *>()},{"BISHOP", vector<Data *>()},{"BLACK", vector<Data *>()},{"BLAIR", vector<Data *>()},{"BLAKE", vector<Data *>()},{"BOWEN", vector<Data *>()},{"BOWMAN", vector<Data *>()},{"BOYD", vector<Data *>()},{"BRADLEY", vector<Data *>()},{"BRADY", vector<Data *>()},{"BREWER", vector<Data *>()},{"BROOKS", vector<Data *>()},{"BROWN", vector<Data *>()},{"BRYANT", vector<Data *>()},{"BURGESS", vector<Data *>()},{"BURKE", vector<Data *>()},{"BURNS", vector<Data *>()},{"BURTON", vector<Data *>()},{"BUSH", vector<Data *>()},{"BUTLER", vector<Data *>()},{"BYRD", vector<Data *>()},{"CABRERA", vector<Data *>()},{"CALDERON", vector<Data *>()},{"CALDWELL", vector<Data *>()},{"CAMACHO", vector<Data *>()},{"CAMPBELL", vector<Data *>()},{"CAMPOS", vector<Data *>()},{"CANNON", vector<Data *>()},{"CARDENAS", vector<Data *>()},{"CARLSON", vector<Data *>()},{"CARPENTER", vector<Data *>()},{"CARR", vector<Data *>()},{"CARRILLO", vector<Data *>()},{"CARROLL", vector<Data *>()},{"CARTER", vector<Data *>()},{"CASTANEDA", vector<Data *>()},{"CASTILLO", vector<Data *>()},{"CASTRO", vector<Data *>()},{"CERVANTES", vector<Data *>()},{"CHAMBERS", vector<Data *>()},{"CHAN", vector<Data *>()},{"CHANDLER", vector<Data *>()},{"CHANG", vector<Data *>()},{"CHAPMAN", vector<Data *>()},{"CHAVEZ", vector<Data *>()},{"CHEN", vector<Data *>()},{"CHRISTENSEN", vector<Data *>()},{"CLARK", vector<Data *>()},{"CLARKE", vector<Data *>()},{"COHEN", vector<Data *>()},{"COLE", vector<Data *>()},{"COLEMAN", vector<Data *>()},{"COLLINS", vector<Data *>()},{"COLON", vector<Data *>()},{"CONTRERAS", vector<Data *>()},{"COOK", vector<Data *>()},{"COOPER", vector<Data *>()},{"CORTEZ", vector<Data *>()},{"COX", vector<Data *>()},{"CRAIG", vector<Data *>()},{"CRAWFORD", vector<Data *>()},{"CROSS", vector<Data *>()},{"CRUZ", vector<Data *>()},{"CUMMINGS", vector<Data *>()},{"CUNNINGHAM", vector<Data *>()},{"CURRY", vector<Data *>()},{"CURTIS", vector<Data *>()},{"DANIEL", vector<Data *>()},{"DANIELS", vector<Data *>()},{"DAVIDSON", vector<Data *>()},{"DAVIS", vector<Data *>()},{"DAWSON", vector<Data *>()},{"DAY", vector<Data *>()},{"DEAN", vector<Data *>()},{"DELACRUZ", vector<Data *>()},{"DELEON", vector<Data *>()},{"DELGADO", vector<Data *>()},{"DENNIS", vector<Data *>()},{"DIAZ", vector<Data *>()},{"DIXON", vector<Data *>()},{"DOMINGUEZ", vector<Data *>()},{"DOUGLAS", vector<Data *>()},{"DOYLE", vector<Data *>()},{"DUNCAN", vector<Data *>()},{"DUNN", vector<Data *>()},{"DURAN", vector<Data *>()},{"EDWARDS", vector<Data *>()},{"ELLIOTT", vector<Data *>()},{"ELLIS", vector<Data *>()},{"ERICKSON", vector<Data *>()},{"ESPINOZA", vector<Data *>()},{"ESTRADA", vector<Data *>()},{"EVANS", vector<Data *>()},{"FARMER", vector<Data *>()},{"FERGUSON", vector<Data *>()},{"FERNANDEZ", vector<Data *>()},{"FIELDS", vector<Data *>()},{"FIGUEROA", vector<Data *>()},{"FISCHER", vector<Data *>()},{"FISHER", vector<Data *>()},{"FITZGERALD", vector<Data *>()},{"FLEMING", vector<Data *>()},{"FLETCHER", vector<Data *>()},{"FLORES", vector<Data *>()},{"FORD", vector<Data *>()},{"FOSTER", vector<Data *>()},{"FOWLER", vector<Data *>()},{"FOX", vector<Data *>()},{"FRANCIS", vector<Data *>()},{"FRANCO", vector<Data *>()},{"FRANK", vector<Data *>()},{"FRANKLIN", vector<Data *>()},{"FRAZIER", vector<Data *>()},{"FREEMAN", vector<Data *>()},{"FUENTES", vector<Data *>()},{"FULLER", vector<Data *>()},{"GALLAGHER", vector<Data *>()},{"GALLEGOS", vector<Data *>()},{"GARCIA", vector<Data *>()},{"GARDNER", vector<Data *>()},{"GARNER", vector<Data *>()},{"GARRETT", vector<Data *>()},{"GARZA", vector<Data *>()},{"GEORGE", vector<Data *>()},{"GIBSON", vector<Data *>()},{"GILBERT", vector<Data *>()},{"GILL", vector<Data *>()},{"GOMEZ", vector<Data *>()},{"GONZALES", vector<Data *>()},{"GONZALEZ", vector<Data *>()},{"GOODMAN", vector<Data *>()},{"GOODWIN", vector<Data *>()},{"GORDON", vector<Data *>()},{"GRAHAM", vector<Data *>()},{"GRANT", vector<Data *>()},{"GRAVES", vector<Data *>()},{"GRAY", vector<Data *>()},{"GREEN", vector<Data *>()},{"GREENE", vector<Data *>()},{"GREGORY", vector<Data *>()},{"GRIFFIN", vector<Data *>()},{"GRIFFITH", vector<Data *>()},{"GROSS", vector<Data *>()},{"GUERRA", vector<Data *>()},{"GUERRERO", vector<Data *>()},{"GUTIERREZ", vector<Data *>()},{"GUZMAN", vector<Data *>()},{"HAIL", vector<Data *>()},{"HALE", vector<Data *>()},{"HALL", vector<Data *>()},{"HAMILTON", vector<Data *>()},{"HAMMOND", vector<Data *>()},{"HAMPTON", vector<Data *>()},{"HANSEN", vector<Data *>()},{"HANSON", vector<Data *>()},{"HARDY", vector<Data *>()},{"HARMON", vector<Data *>()},{"HARPER", vector<Data *>()},{"HARRINGTON", vector<Data *>()},{"HARRIS", vector<Data *>()},{"HARRISON", vector<Data *>()},{"HART", vector<Data *>()},{"HARVEY", vector<Data *>()},{"HAWKINS", vector<Data *>()},{"HAYES", vector<Data *>()},{"HAYNES", vector<Data *>()},{"HENDERSON", vector<Data *>()},{"HENRY", vector<Data *>()},{"HERNANDEZ", vector<Data *>()},{"HERRERA", vector<Data *>()},{"HICKS", vector<Data *>()},{"HIGGINS", vector<Data *>()},{"HILL", vector<Data *>()},{"HINES", vector<Data *>()},{"HODGES", vector<Data *>()},{"HOFFMAN", vector<Data *>()},{"HOLLAND", vector<Data *>()},{"HOLMES", vector<Data *>()},{"HOLT", vector<Data *>()},{"HOPKINS", vector<Data *>()},{"HORTON", vector<Data *>()},{"HOWARD", vector<Data *>()},{"HOWELL", vector<Data *>()},{"HUANG", vector<Data *>()},{"HUBBARD", vector<Data *>()},{"HUDSON", vector<Data *>()},{"HUGHES", vector<Data *>()},{"HUNT", vector<Data *>()},{"HUNTER", vector<Data *>()},{"INGRAM", vector<Data *>()},{"JACKSON", vector<Data *>()},{"JACOBS", vector<Data *>()},{"JAMES", vector<Data *>()},{"JENKINS", vector<Data *>()},{"JENNINGS", vector<Data *>()},{"JENSEN", vector<Data *>()},{"JIMENEZ", vector<Data *>()},{"JOHNSON", vector<Data *>()},{"JOHNSTON", vector<Data *>()},{"JONES", vector<Data *>()},{"JORDAN", vector<Data *>()},{"JOSEPH", vector<Data *>()},{"JUAREZ", vector<Data *>()},{"KELLER", vector<Data *>()},{"KELLEY", vector<Data *>()},{"KELLY", vector<Data *>()},{"KENNEDY", vector<Data *>()},{"KHAN", vector<Data *>()},{"KIM", vector<Data *>()},{"KING", vector<Data *>()},{"KLEIN", vector<Data *>()},{"KNIGHT", vector<Data *>()},{"LAMBERT", vector<Data *>()},{"LANE", vector<Data *>()},{"LARA", vector<Data *>()},{"LARSON", vector<Data *>()},{"LAWRENCE", vector<Data *>()},{"LAWSON", vector<Data *>()},{"LE", vector<Data *>()},{"LEE", vector<Data *>()},{"LEON", vector<Data *>()},{"LEONARD", vector<Data *>()},{"LEWIS", vector<Data *>()},{"LI", vector<Data *>()},{"LIN", vector<Data *>()},{"LITTLE", vector<Data *>()},{"LIU", vector<Data *>()},{"LOGAN", vector<Data *>()},{"LONG", vector<Data *>()},{"LOPEZ", vector<Data *>()},{"LOVE", vector<Data *>()},{"LOWE", vector<Data *>()},{"LUCAS", vector<Data *>()},{"LUNA", vector<Data *>()},{"LYNCH", vector<Data *>()},{"LYONS", vector<Data *>()},{"MACK", vector<Data *>()},{"MALDONADO", vector<Data *>()},{"MALONE", vector<Data *>()},{"MANN", vector<Data *>()},{"MANNING", vector<Data *>()},{"MARQUEZ", vector<Data *>()},{"MARSHALL", vector<Data *>()},{"MARTIN", vector<Data *>()},{"MARTINEZ", vector<Data *>()},{"MASON", vector<Data *>()},{"MATTHEWS", vector<Data *>()},{"MAXWELL", vector<Data *>()},{"MAY", vector<Data *>()},{"MCCARTHY", vector<Data *>()},{"MCCOY", vector<Data *>()},{"MCDANIEL", vector<Data *>()},{"MCDONALD", vector<Data *>()},{"MCGEE", vector<Data *>()},{"MCKINNEY", vector<Data *>()},{"MCLAUGHLIN", vector<Data *>()},{"MEDINA", vector<Data *>()},{"MEJIA", vector<Data *>()},{"MENDEZ", vector<Data *>()},{"MENDOZA", vector<Data *>()},{"MEYER", vector<Data *>()},{"MILES", vector<Data *>()},{"MILLER", vector<Data *>()},{"MILLS", vector<Data *>()},{"MIRANDA", vector<Data *>()},{"MITCHELL", vector<Data *>()},{"MOLINA", vector<Data *>()},{"MONTGOMERY", vector<Data *>()},{"MONTOYA", vector<Data *>()},{"MOORE", vector<Data *>()},{"MORALES", vector<Data *>()},{"MORAN", vector<Data *>()},{"MORENO", vector<Data *>()},{"MORGAN", vector<Data *>()},{"MORRIS", vector<Data *>()},{"MORRISON", vector<Data *>()},{"MOSS", vector<Data *>()},{"MULLINS", vector<Data *>()},{"MUNOZ", vector<Data *>()},{"MURPHY", vector<Data *>()},{"MURRAY", vector<Data *>()},{"MYERS", vector<Data *>()},{"NAVARRO", vector<Data *>()},{"NEAL", vector<Data *>()},{"NELSON", vector<Data *>()},{"NEWMAN", vector<Data *>()},{"NEWTON", vector<Data *>()},{"NGUYEN", vector<Data *>()},{"NICHOLS", vector<Data *>()},{"NORMAN", vector<Data *>()},{"NORRIS", vector<Data *>()},{"NUNEZ", vector<Data *>()},{"OBRIEN", vector<Data *>()},{"OCHOA", vector<Data *>()},{"OCONNOR", vector<Data *>()},{"OLIVER", vector<Data *>()},{"OLSON", vector<Data *>()},{"ORTEGA", vector<Data *>()},{"ORTIZ", vector<Data *>()},{"OWENS", vector<Data *>()},{"PACHECO", vector<Data *>()},{"PADILLA", vector<Data *>()},{"PAGE", vector<Data *>()},{"PALMER", vector<Data *>()},{"PARK", vector<Data *>()},{"PARKER", vector<Data *>()},{"PARKS", vector<Data *>()},{"PARSONS", vector<Data *>()},{"PATEL", vector<Data *>()},{"PATTERSON", vector<Data *>()},{"PAUL", vector<Data *>()},{"PAYNE", vector<Data *>()},{"PEARSON", vector<Data *>()},{"PENA", vector<Data *>()},{"PEREZ", vector<Data *>()},{"PERKINS", vector<Data *>()},{"PERRY", vector<Data *>()},{"PERSON", vector<Data *>()},{"PETERS", vector<Data *>()},{"PETERSON", vector<Data *>()},{"PHAM", vector<Data *>()},{"PHILLIPS", vector<Data *>()},{"PIERCE", vector<Data *>()},{"PORTER", vector<Data *>()},{"POTTER", vector<Data *>()},{"POWELL", vector<Data *>()},{"POWERS", vector<Data *>()},{"PRICE", vector<Data *>()},{"QUINN", vector<Data *>()},{"RAMIREZ", vector<Data *>()},{"RAMOS", vector<Data *>()},{"RAMSEY", vector<Data *>()},{"RAY", vector<Data *>()},{"REED", vector<Data *>()},{"REESE", vector<Data *>()},{"REEVES", vector<Data *>()},{"REID", vector<Data *>()},{"REYES", vector<Data *>()},{"REYNOLDS", vector<Data *>()},{"RHODES", vector<Data *>()},{"RICE", vector<Data *>()},{"RICHARDS", vector<Data *>()},{"RICHARDSON", vector<Data *>()},{"RILEY", vector<Data *>()},{"RIOS", vector<Data *>()},{"RIVAS", vector<Data *>()},{"RIVERA", vector<Data *>()},{"ROBBINS", vector<Data *>()},{"ROBERTS", vector<Data *>()},{"ROBERTSON", vector<Data *>()},{"ROBINSON", vector<Data *>()},{"ROBLES", vector<Data *>()},{"RODGERS", vector<Data *>()},{"RODRIGUEZ", vector<Data *>()},{"ROGERS", vector<Data *>()},{"ROJAS", vector<Data *>()},{"ROMAN", vector<Data *>()},{"ROMERO", vector<Data *>()},{"ROSALES", vector<Data *>()},{"ROSE", vector<Data *>()},{"ROSS", vector<Data *>()},{"ROWE", vector<Data *>()},{"RUIZ", vector<Data *>()},{"RUSSELL", vector<Data *>()},{"RYAN", vector<Data *>()},{"SALAZAR", vector<Data *>()},{"SALINAS", vector<Data *>()},{"SANCHEZ", vector<Data *>()},{"SANDERS", vector<Data *>()},{"SANDOVAL", vector<Data *>()},{"SANTIAGO", vector<Data *>()},{"SANTOS", vector<Data *>()},{"SAUNDERS", vector<Data *>()},{"SCHMIDT", vector<Data *>()},{"SCHNEIDER", vector<Data *>()},{"SCHROEDER", vector<Data *>()},{"SCHULTZ", vector<Data *>()},{"SCHWARTZ", vector<Data *>()},{"SCOTT", vector<Data *>()},{"SERRANO", vector<Data *>()},{"SHARP", vector<Data *>()},{"SHAW", vector<Data *>()},{"SHELTON", vector<Data *>()},{"SHERMAN", vector<Data *>()},{"SILVA", vector<Data *>()},{"SIMMONS", vector<Data *>()},{"SIMON", vector<Data *>()},{"SIMPSON", vector<Data *>()},{"SIMS", vector<Data *>()},{"SINGH", vector<Data *>()},{"SNYDER", vector<Data *>()},{"SOLIS", vector<Data *>()},{"SOTO", vector<Data *>()},{"SPENCER", vector<Data *>()},{"STANLEY", vector<Data *>()},{"STEELE", vector<Data *>()},{"STEPHENS", vector<Data *>()},{"STEVENS", vector<Data *>()},{"STEVENSON", vector<Data *>()},{"STEWART", vector<Data *>()},{"STONE", vector<Data *>()},{"STRICKLAND", vector<Data *>()},{"SULLIVAN", vector<Data *>()},{"SUTTON", vector<Data *>()},{"SWANSON", vector<Data *>()},{"TATE", vector<Data *>()},{"TAYLOR", vector<Data *>()},{"TERRY", vector<Data *>()},{"THOMAS", vector<Data *>()},{"THOMPSON", vector<Data *>()},{"THORNTON", vector<Data *>()},{"TODD", vector<Data *>()},{"TORRES", vector<Data *>()},{"TOWNSEND", vector<Data *>()},{"TRAN", vector<Data *>()},{"TRUJILLO", vector<Data *>()},{"TUCKER", vector<Data *>()},{"TURNER", vector<Data *>()},{"VALDEZ", vector<Data *>()},{"VALENCIA", vector<Data *>()},{"VARGAS", vector<Data *>()},{"VASQUEZ", vector<Data *>()},{"VAUGHN", vector<Data *>()},{"VAZQUEZ", vector<Data *>()},{"VEGA", vector<Data *>()},{"VELASQUEZ", vector<Data *>()},{"WADE", vector<Data *>()},{"WAGNER", vector<Data *>()},{"WALKER", vector<Data *>()},{"WALLACE", vector<Data *>()},{"WALSH", vector<Data *>()},{"WALTERS", vector<Data *>()},{"WALTON", vector<Data *>()},{"WANG", vector<Data *>()},{"WARD", vector<Data *>()},{"WARNER", vector<Data *>()},{"WARREN", vector<Data *>()},{"WASHINGTON", vector<Data *>()},{"WATERS", vector<Data *>()},{"WATKINS", vector<Data *>()},{"WATSON", vector<Data *>()},{"WATTS", vector<Data *>()},{"WEAVER", vector<Data *>()},{"WEBB", vector<Data *>()},{"WEBER", vector<Data *>()},{"WEBSTER", vector<Data *>()},{"WELCH", vector<Data *>()},{"WELLS", vector<Data *>()},{"WEST", vector<Data *>()},{"WHEELER", vector<Data *>()},{"WHITE", vector<Data *>()},{"WILLIAMS", vector<Data *>()},{"WILLIAMSON", vector<Data *>()},{"WILLIS", vector<Data *>()},{"WILSON", vector<Data *>()},{"WISE", vector<Data *>()},{"WOLF", vector<Data *>()},{"WOLFE", vector<Data *>()},{"WONG", vector<Data *>()},{"WOOD", vector<Data *>()},{"WOODS", vector<Data *>()},{"WRIGHT", vector<Data *>()},{"WU", vector<Data *>()},{"YANG", vector<Data *>()},{"YOUNG", vector<Data *>()},{"ZHANG", vector<Data *>()},{"ZIMMERMAN", vector<Data *>()}};

bool comparator(const Data* person1, const Data* person2) {
//    if (person1 -> lastName > person2 -> lastName)
//        return false;
//    if (person1 -> lastName < person2 -> lastName)
//        return true;
//    if (person1 -> firstName > person2 -> firstName)
//        return false;
//    if (person1 -> firstName < person2 -> firstName)
//        return true;
    if (person1 -> ssn >= person2 -> ssn)
        return false;
    else
        return true;
}

void sortDataList(list<Data *> &l) {

   // Data arr[30] = {};
    // Fill this in

    if(l.front()->lastName == l.back()->lastName){
        l.sort(comparator);
        return;
    }


    for (auto it = l.begin(); it != l.end(); ++it) {
        firstMap[(*it)->firstName].push_back(*it);
    }

    for (auto it = firstMap.begin(); it != firstMap.end(); ++it) {
        auto pointer = it->second;
        for (auto it2 = pointer.begin(); it2 != pointer.end(); ++it2) {
            lastMap[(*it2)->lastName].push_back(*it2);
        }
    }


    auto listIt = l.begin();
    for (auto &it : lastMap) {
        auto pointer = it.second;
        int k = pointer.size() - 1;
        for (int i = 0; i <= k; ++i) {
            if (i != k && pointer[i]->firstName == pointer[i + 1]->firstName) {
                vector<Data *> xst = {};
                int z = i;
                xst.push_back(pointer[i]); //this one
                ++i;
                xst.push_back(pointer[i]); //the next one
                while(i < k && pointer[i + 1]->firstName == pointer[z]->firstName) {
                    ++i;
                    xst.push_back(pointer[i]); //this one
                }
                sort(xst.begin(),xst.end(),comparator);
                for (auto &rep : xst){
                    *listIt = rep;
                    ++listIt;
                }
                xst = {};
            }else{
                *listIt = pointer[i];
                ++listIt;
            }

        }

    }


    }



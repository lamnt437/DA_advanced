//create a new more specific (phonebook) lib that impliments abstract (symbol table) library
//use typedef Entry PhoneEntry



//add new api to phonebook to avoid direct access to data structure

//build api for phoneentry
//in phonebook.c
char * getNameFromEntry(PhoneEntry e){
	return (char *)e.key;
}

// getNumber
long getNumberFromEntry(PhoneEntry e){
	return *((long *)e.value);
}


//build api for symboltable
//in symboltable.c
void *getKeyFromEntry(Entry e){
	return e.key;
}

void *getValueFromEntry(Entry e){
	return e.value;
}

//apply new symboltable api to phonebook
//in phonebook.c
char * getNameFromEntry(PhoneEntry e){
	return (char *)getKeyFromEntry(e);
}

// getNumber
long getNumberFromEntry(PhoneEntry e){
	return *((long *)getValueFromEntry(e));
}

//apply to application
//to print out name and key from phoneentry, use getNameFromPhoneEntry and getNumberFromPhoneEntry

//hide symbol table struct in other filie

//use pointer
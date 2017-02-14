// call_function.c - A sample of calling python functions from C code
//
#include <Python.h>

int main(int argc, char *argv[]){
    PyObject *pName, *pModule, *pDict, *pFunc, *pValue;
    PyObject *pArgs = NULL;

    if(argc < 3){
	    printf("Usage: exe_name python_source function_name\n");
	    return 1;
    }

	// initialize the Python Interpreter
	Py_Initialize();
	// Add current directory to Module Search Path
	PyObject *sysPath = PySys_GetObject((char*)"path");
	PyObject *programName = PyString_FromString(".");
	PyList_Append(sysPath, programName);
	Py_DECREF(programName);
	// Build the name object
	pName = PyString_FromString(argv[1]);
	// Load the module object
	pModule = PyImport_Import(pName);
	printf("pModule Addr: %p\n", pModule);
	if(pModule == NULL){
		// module not found.
		Py_DECREF(pName);
		return 1;	
	}
	// pDict is a borrowed reference
	pDict = PyModule_GetDict(pModule);
	printf("pDict loaded\n");
	// pFunc is also a borrowed reference
	pFunc = PyDict_GetItemString(pDict, argv[2]);

	if(PyCallable_Check(pFunc)){
		// Prepare the argumten list for call 
        FILE *f = fopen("x.txt", "rb");
		fseek(f, 0, SEEK_END);
		long fsize = ftell(f);
		fseek(f, 0, SEEK_SET); // rewind(f);

		char *string = malloc(fsize + 1);
		fread(string, fsize, 1, f);
		fclose(f);

   		string[fsize] = 0;
		if(argc > 3 ){
			pArgs = PyTuple_New(argc -3);
			for(int i = 0; i < argc -3; i++){
				pValue = PyString_FromString(string); 
				if(!pValue){
					PyErr_Print();
					return 1;
				}
				PyTuple_SetItem(pArgs, i, pValue);
			}
			pValue = PyObject_CallObject(pFunc, pArgs);
		}
		
		if(pArgs != NULL){
			Py_DECREF(pArgs);
		} else {
			pValue = PyObject_CallObject(pFunc, NULL);
		}
		free(string);
		// PyObject_CallObject(pFunc, NULL);
	} else
	{
		PyErr_Print();
	}

	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);

	// Finish the Python Interpreter
	Py_Finalize();
	return 0;
}

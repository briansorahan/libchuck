#include <Python.h>
#include <assert.h>
#include <chuck.h>

using chuck::Chuck;

static Chuck * ck = NULL;

static PyObject * pychuck_Spork(PyObject * self, PyObject * args) {
    assert(ck);

    int numfiles;
    const char ** filenames;

    if (! PyArg_ParseTuple(args, "i", &numfiles)) {
        return NULL;
    }

    return Py_None;
}

static PyMethodDef PyChuckMethods[] = {
    { "Spork",         pychuck_Spork,         METH_VARARGS,         "Spork a chuck file"               },
    // sentinel
    { NULL,            NULL,                  0,                    NULL                               }
};

PyMODINIT_FUNC initpychuck(void) {
    chuck::Create(&ck);
    (void) Py_InitModule("pychuck", PyChuckMethods);
}

#include <Python.h>
#include <assert.h>
#include <chuck.h>

using chuck::Chuck;

static Chuck * ck = NULL;

static PyObject * pychuck_Spork(PyObject * self, PyObject * args) {
    assert(ck);

    // TODO: support sporking more than one file
    // int numfiles;
    // const char ** filenames;

    const char * filename;

    if (! PyArg_ParseTuple(args, "s", &filename)) {
        return NULL;
    }

    const char * filenames[] = { filename };
    // int sporked = ck->Spork(1, filenames);
    ck->Spork(1, filenames);

    // TODO: return a useful value
    return Py_None;
}

static PyObject * pychuck_Run(PyObject * self, PyObject * args) {
    assert(ck);

    ck->Run();

    // TODO: return a useful value
    return Py_None;
}

static PyMethodDef PyChuckMethods[] = {
    { "Spork",         pychuck_Spork,         METH_VARARGS,         "Spork a chuck file"               },
    { "Run",           pychuck_Run,           METH_VARARGS,         "Let the chuck vm run"             },
    // sentinel
    { NULL,            NULL,                  0,                    NULL                               }
};

PyMODINIT_FUNC initpychuck(void) {
    chuck::Create(&ck);
    (void) Py_InitModule("pychuck", PyChuckMethods);
}

#include <Python.h>

static PyObject* dot(PyObject* self, PyObject* args) {
    int size; PyObject* A; PyObject* B;
    if (!PyArg_ParseTuple(args, "iOO", &size, &A, &B)) {
        PyErr_SetString(PyExc_TypeError, "invalid input");
        return NULL;
    }

    PyObject* answer = PyList_New(0);
    for (int i = 0; i < size; ++i) {
        PyObject* str = PyList_New(0);
        for (int j = 0; j < size; ++j) {
            double element = 0.0;
            for (int k = 0; k < size; ++k)
                if (i < PyList_Size(A) && k < PyList_Size(PyList_GetItem(A, i)) && k < PyList_Size(B) && j < PyList_Size(PyList_GetItem(B, k))) {
                    double x = PyFloat_AsDouble(PyList_GetItem(PyList_GetItem(A, i), k));
                    double y = PyFloat_AsDouble(PyList_GetItem(PyList_GetItem(B, k), j));
                    element += x*y;
                }
            PyList_Append(str, PyFloat_FromDouble(element));
        }
        PyList_Append(answer, str);
        Py_DECREF(str);
    }

    Py_DECREF(B); Py_DECREF(A);
    return Py_BuildValue("O", answer);
}

static PyMethodDef methods[] = {
    {"dot", dot, METH_VARARGS, "help func_1"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT, "matrix", "pymatrixdot", -1, methods
};

PyMODINIT_FUNC PyInit_matrix(void) {
    return PyModule_Create(&module);
}
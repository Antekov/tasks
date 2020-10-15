#include <Python.h>

PyObject* matrix_dot(PyObject* self, PyObject* args) {
    int n;
    PyObject* pyA;
    PyObject* pyB;

    if (!PyArg_ParseTuple(args, "iOO", &n, &pyA, &pyB)) {
        return NULL;
    }

    double** A = NULL;
    double** B = NULL;
    double** C = NULL;

    A = (double**) malloc(n * sizeof(double*));
    B = (double**) malloc(n * sizeof(double*));
    C = (double**) malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        A[i] = (double*) malloc(n * sizeof(double));
        B[i] = (double*) malloc(n * sizeof(double));
        C[i] = (double*) malloc(n * sizeof(double));

        for (int j = 0; j < n; j++) {
            if (i < PyList_Size(pyA) && j < PyList_Size(PyList_GetItem(pyA, i))) {
                A[i][j] = PyFloat_AsDouble(PyList_GetItem(PyList_GetItem(pyA, i), j));
            }
            else {
                A[i][j] = 0;
            }
            if (i < PyList_Size(pyB) && j < PyList_Size(PyList_GetItem(pyB, i))) {
                B[i][j] = PyFloat_AsDouble(PyList_GetItem(PyList_GetItem(pyB, i), j));
            }
            else {
                B[i][j] = 0;
            }
            C[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double s = 0;
            for (int k = 0; k < n; k++) {
                s += A[i][k] * B[k][j];
            }
            C[i][j] = s;
        }
    }

    PyObject* result = PyList_New(0);

    for (int i = 0; i < n; i++) {
        PyObject* row = PyList_New(0);
        for (int j = 0; j < n; j++) {
            PyList_Append(row, PyFloat_FromDouble(C[i][j]));
        }
        PyList_Append(result, row);
        Py_DECREF(row);
    }

    Py_DECREF(pyA);
    Py_DECREF(pyB);

    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }

    free(A);
    free(B);
    free(C);

    return Py_BuildValue("O", result);
}

static PyMethodDef matrix_methods[] = {
    { "dot", (PyCFunction)matrix_dot, METH_VARARGS, NULL },
    { NULL, NULL, 0, NULL }
};

static PyModuleDef matrix_module = {
    PyModuleDef_HEAD_INIT,
    "matrix",
    "Provides some matrix functions, but faster",
    0,
    matrix_methods
};

PyMODINIT_FUNC PyInit_matrix() {
    return PyModule_Create(&matrix_module);
}

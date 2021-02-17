/****************************************************************************
** Meta object code from reading C++ file 'tabViewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Headers/Pages/tabViewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tabViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Worker_t {
    QByteArrayData data[13];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Worker_t qt_meta_stringdata_Worker = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Worker"
QT_MOC_LITERAL(1, 7, 7), // "updated"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 8), // "finished"
QT_MOC_LITERAL(4, 25, 14), // "rawDataUpdated"
QT_MOC_LITERAL(5, 40, 4), // "data"
QT_MOC_LITERAL(6, 45, 17), // "percentageUpdated"
QT_MOC_LITERAL(7, 63, 5), // "value"
QT_MOC_LITERAL(8, 69, 4), // "stop"
QT_MOC_LITERAL(9, 74, 5), // "pause"
QT_MOC_LITERAL(10, 80, 11), // "togglePause"
QT_MOC_LITERAL(11, 92, 6), // "resume"
QT_MOC_LITERAL(12, 99, 16) // "changePercentage"

    },
    "Worker\0updated\0\0finished\0rawDataUpdated\0"
    "data\0percentageUpdated\0value\0stop\0"
    "pause\0togglePause\0resume\0changePercentage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Worker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    1,   61,    2, 0x06 /* Public */,
       6,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   67,    2, 0x0a /* Public */,
       9,    0,   68,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x0a /* Public */,
      11,    0,   70,    2, 0x0a /* Public */,
      12,    1,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    5,
    QMetaType::Void, QMetaType::Float,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    7,

       0        // eod
};

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updated(); break;
        case 1: _t->finished(); break;
        case 2: _t->rawDataUpdated((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->percentageUpdated((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->stop(); break;
        case 5: _t->pause(); break;
        case 6: _t->togglePause(); break;
        case 7: _t->resume(); break;
        case 8: _t->changePercentage((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Worker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::updated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Worker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::finished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Worker::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::rawDataUpdated)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Worker::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::percentageUpdated)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Worker::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_Worker.data,
    qt_meta_data_Worker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Worker.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Worker::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Worker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Worker::rawDataUpdated(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Worker::percentageUpdated(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_TabViewer_t {
    QByteArrayData data[22];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TabViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TabViewer_t qt_meta_stringdata_TabViewer = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TabViewer"
QT_MOC_LITERAL(1, 10, 4), // "kill"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 5), // "start"
QT_MOC_LITERAL(4, 22, 5), // "pause"
QT_MOC_LITERAL(5, 28, 11), // "togglePause"
QT_MOC_LITERAL(6, 40, 13), // "setPercentage"
QT_MOC_LITERAL(7, 54, 5), // "value"
QT_MOC_LITERAL(8, 60, 12), // "submitAction"
QT_MOC_LITERAL(9, 73, 12), // "pathSelected"
QT_MOC_LITERAL(10, 86, 6), // "folder"
QT_MOC_LITERAL(11, 93, 11), // "treeClicked"
QT_MOC_LITERAL(12, 105, 11), // "QModelIndex"
QT_MOC_LITERAL(13, 117, 5), // "index"
QT_MOC_LITERAL(14, 123, 15), // "pauseBtnClicked"
QT_MOC_LITERAL(15, 139, 17), // "percentageUpdated"
QT_MOC_LITERAL(16, 157, 17), // "userChangedSlider"
QT_MOC_LITERAL(17, 175, 14), // "chimeraUpdated"
QT_MOC_LITERAL(18, 190, 14), // "rawDataUpdated"
QT_MOC_LITERAL(19, 205, 4), // "data"
QT_MOC_LITERAL(20, 210, 14), // "rawItemClicked"
QT_MOC_LITERAL(21, 225, 16) // "QListWidgetItem*"

    },
    "TabViewer\0kill\0\0start\0pause\0togglePause\0"
    "setPercentage\0value\0submitAction\0"
    "pathSelected\0folder\0treeClicked\0"
    "QModelIndex\0index\0pauseBtnClicked\0"
    "percentageUpdated\0userChangedSlider\0"
    "chimeraUpdated\0rawDataUpdated\0data\0"
    "rawItemClicked\0QListWidgetItem*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TabViewer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    0,   86,    2, 0x06 /* Public */,
       5,    0,   87,    2, 0x06 /* Public */,
       6,    1,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   91,    2, 0x0a /* Public */,
       9,    1,   92,    2, 0x0a /* Public */,
      11,    1,   95,    2, 0x0a /* Public */,
      14,    0,   98,    2, 0x0a /* Public */,
      15,    1,   99,    2, 0x0a /* Public */,
      16,    0,  102,    2, 0x0a /* Public */,
      17,    0,  103,    2, 0x0a /* Public */,
      18,    1,  104,    2, 0x0a /* Public */,
      20,    1,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   19,
    QMetaType::Void, 0x80000000 | 21,   13,

       0        // eod
};

void TabViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TabViewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->kill(); break;
        case 1: _t->start(); break;
        case 2: _t->pause(); break;
        case 3: _t->togglePause(); break;
        case 4: _t->setPercentage((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->submitAction(); break;
        case 6: _t->pathSelected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->treeClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->pauseBtnClicked(); break;
        case 9: _t->percentageUpdated((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->userChangedSlider(); break;
        case 11: _t->chimeraUpdated(); break;
        case 12: _t->rawDataUpdated((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 13: _t->rawItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TabViewer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TabViewer::kill)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TabViewer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TabViewer::start)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TabViewer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TabViewer::pause)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TabViewer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TabViewer::togglePause)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TabViewer::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TabViewer::setPercentage)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TabViewer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_TabViewer.data,
    qt_meta_data_TabViewer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TabViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TabViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TabViewer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TabViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void TabViewer::kill()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TabViewer::start()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TabViewer::pause()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TabViewer::togglePause()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void TabViewer::setPercentage(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

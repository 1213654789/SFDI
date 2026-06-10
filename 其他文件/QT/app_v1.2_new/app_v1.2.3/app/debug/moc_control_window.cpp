/****************************************************************************
** Meta object code from reading C++ file 'control_window.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../control_window.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'control_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN14control_windowE_t {};
} // unnamed namespace

template <> constexpr inline auto control_window::qt_create_metaobjectdata<qt_meta_tag_ZN14control_windowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "control_window",
        "on_Advanced_Button_clicked",
        "",
        "on_actionSerialHelper_triggered",
        "on_actionabout_triggered",
        "on_actionexit_triggered",
        "on_find_device_clicked",
        "on_open_device_clicked",
        "on_close_device_clicked",
        "on_single_acquisition_clicked",
        "on_continuous_acquisition_clicked",
        "on_stops_acquisition_clicked",
        "on_save_BMP_clicked",
        "on_save_PNG_clicked",
        "on_save_location_clicked",
        "slot_display",
        "slot_displayImage",
        "QImage",
        "image",
        "on_weightphoto_valueChanged",
        "val",
        "on_highphoto_valueChanged",
        "on_triggerMode_currentIndexChanged",
        "index",
        "on_triggerSource_currentIndexChanged",
        "mapTriggerModeValue",
        "text",
        "mapTriggerSourceValue",
        "mapTriggerActivationValue",
        "on_Exit_Button_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_Advanced_Button_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionSerialHelper_triggered'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionabout_triggered'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionexit_triggered'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_find_device_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_open_device_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_close_device_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_single_acquisition_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_continuous_acquisition_clicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_stops_acquisition_clicked'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_save_BMP_clicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_save_PNG_clicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_save_location_clicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slot_display'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'slot_displayImage'
        QtMocHelpers::SlotData<void(QImage)>(16, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 17, 18 },
        }}),
        // Slot 'on_weightphoto_valueChanged'
        QtMocHelpers::SlotData<void(int)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 20 },
        }}),
        // Slot 'on_highphoto_valueChanged'
        QtMocHelpers::SlotData<void(int)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 20 },
        }}),
        // Slot 'on_triggerMode_currentIndexChanged'
        QtMocHelpers::SlotData<void(int)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 23 },
        }}),
        // Slot 'on_triggerSource_currentIndexChanged'
        QtMocHelpers::SlotData<void(int)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 23 },
        }}),
        // Slot 'mapTriggerModeValue'
        QtMocHelpers::SlotData<int(const QString &)>(25, 2, QMC::AccessPrivate, QMetaType::Int, {{
            { QMetaType::QString, 26 },
        }}),
        // Slot 'mapTriggerSourceValue'
        QtMocHelpers::SlotData<int(const QString &)>(27, 2, QMC::AccessPrivate, QMetaType::Int, {{
            { QMetaType::QString, 26 },
        }}),
        // Slot 'mapTriggerActivationValue'
        QtMocHelpers::SlotData<int(const QString &)>(28, 2, QMC::AccessPrivate, QMetaType::Int, {{
            { QMetaType::QString, 26 },
        }}),
        // Slot 'on_Exit_Button_clicked'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<control_window, qt_meta_tag_ZN14control_windowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject control_window::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14control_windowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14control_windowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14control_windowE_t>.metaTypes,
    nullptr
} };

void control_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<control_window *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_Advanced_Button_clicked(); break;
        case 1: _t->on_actionSerialHelper_triggered(); break;
        case 2: _t->on_actionabout_triggered(); break;
        case 3: _t->on_actionexit_triggered(); break;
        case 4: _t->on_find_device_clicked(); break;
        case 5: _t->on_open_device_clicked(); break;
        case 6: _t->on_close_device_clicked(); break;
        case 7: _t->on_single_acquisition_clicked(); break;
        case 8: _t->on_continuous_acquisition_clicked(); break;
        case 9: _t->on_stops_acquisition_clicked(); break;
        case 10: _t->on_save_BMP_clicked(); break;
        case 11: _t->on_save_PNG_clicked(); break;
        case 12: _t->on_save_location_clicked(); break;
        case 13: _t->slot_display(); break;
        case 14: _t->slot_displayImage((*reinterpret_cast<std::add_pointer_t<QImage>>(_a[1]))); break;
        case 15: _t->on_weightphoto_valueChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 16: _t->on_highphoto_valueChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->on_triggerMode_currentIndexChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 18: _t->on_triggerSource_currentIndexChanged((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 19: { int _r = _t->mapTriggerModeValue((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 20: { int _r = _t->mapTriggerSourceValue((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 21: { int _r = _t->mapTriggerActivationValue((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 22: _t->on_Exit_Button_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *control_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *control_window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14control_windowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int control_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 23;
    }
    return _id;
}
QT_WARNING_POP

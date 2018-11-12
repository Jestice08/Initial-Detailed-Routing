//
// Created by keren on 9/22/17.
//

#include "DefReader.h"

    void DefReader::set_def_dividerchar(const std::string &string) {

    }

    void DefReader::set_def_busbitchars(const std::string &string) {

    }

    void DefReader::set_def_version(const std::string &string) {

    }

    void DefReader::set_def_design(const std::string &string) {

    }

    void DefReader::set_def_unit(int i) {
        _db.setDefUnit(i);
    }

    void DefReader::set_def_diearea(int i, int i1, int i2, int i3) {
        _db.setDieXl(i);
        _db.setDieYl(i1);
        _db.setDieXh(i2);
        _db.setDieYh(i3);

    }

    void DefReader::add_def_row(const DefParser::Row &row) {
        _db.addRowArray(row);
    }

    void DefReader::add_def_component(const DefParser::Component &component) {
        /*IndexType cellIndex = static_cast<IndexType>(_db.getCellArray().size());
        Cell cell = Cell();
        CellInfo cellInfo = CellInfo();
        cell.setCellIndex(cellIndex);
        cellInfo.setCellIndex(cellIndex);
        cellInfo.setCellName(component.comp_name);
        cellInfo.setMacroName(component.macro_name);
        assert(component.status == "FIXED" || component.status == "PLACED");
        if (component.status == "FIXED") {
            cellInfo.setStatus(PlaceStatusType::FIXED);
        } else {
            cellInfo.setStatus(PlaceStatusType::PLACED);
        }
        assert(component.orient == "N" || component.status == "FS");
        if (component.orient == "N") {
            cell.setOrient(OrientationType::N);
        } else if (component.orient == "FS") {
            cell.setOrient(OrientationType::FS);
        } else if (component.orient == "FN") {
            cell.setOrient(OrientationType::FN);
        } else if (component.orient == "S") {
            cell.setOrient(OrientationType::S);
        } else {
            cell.setOrient(OrientationType::UNDEFINED);
        }
        cell.setX(component.origin[0]);
        cell.setY(component.origin[1]);
        cell.setXInitial(cell.getX());
        cell.setYInitial(cell.getY());
        cellInfo.setUnshrinkedX(cell.getX());
        _db.addCellInfoArray(cellInfo);
        _db.addCellIndexLUT(cellInfo.getCellName(), cellIndex);*/
        _db.addComponentArray(component);
    }

    void DefReader::resize_def_component(int i) {
        _db.getComponentArray().reserve(static_cast<unsigned long>(i));
    }

    void DefReader::add_def_pin(const DefParser::Pin &pin) {
        /*DefPin temp = DefPin();
        IndexType pinIndex = static_cast<IndexType>(_db.getDefPinArray().size());
        temp.setDefPinIndex(pinIndex);
        temp.setPinName(pin.pin_name);
        temp.setNetName(pin.net_name);
        assert(pin.vLayer.size() == 1);
        temp.setX(pin.origin[0]);
        temp.setY(pin.origin[1]);
        temp.setLayer(pin.vLayer[0]);
        temp.setOffsetXl(pin.vBbox[0][0]);
        temp.setOffsetYl(pin.vBbox[0][1]);
        temp.setOffsetXh(pin.vBbox[0][2]);
        temp.setOffsetYh(pin.vBbox[0][3]);
        _db.addDefPinIndexLUT(pin.pin_name, pinIndex);*/
        _db.addPinArray(pin);
    }

    void DefReader::resize_def_pin(int i) {
        _db.getPinArray().reserve(static_cast<unsigned long>(i));
    }

    void DefReader::add_def_net(const DefParser::Net &net) {
        _db.addNetArray(net);
    }

    void DefReader::resize_def_net(int i) {
        _db.getNetArray().reserve(static_cast<unsigned long>(i));
    }

    void DefReader::add_def_track(const DefParser::Track &track) {

    }

    void DefReader::add_def_snetpath(const DefParser::Snetp &snetp) {
        _db.addSnetpArray(snetp);
    }

    void DefReader::add_def_region(const DefParser::Region &region) {
        /*Region temp = Region();
        temp.setRegionName(region.name);
        for (int i = 0; i < region.xh.size(); ++i) {

            temp.setXl(region.xl[i]);
            temp.setXh(region.xh[i]);
            temp.setYl(region.yl[i]);
            temp.setYh(region.yh[i]);
        }*/
    }

    void DefReader::add_def_group(const DefParser::Group &group) {
        _db.addGroupArray(group);

    }

    void DefReader::add_def_via(const DefParser::Via &via) {
        _db.addViaArray(via);
    }

    void DefReader::end_def_design() {
        //DefDataBase::end_def_design();
    }

    void DefReader::resize_def_blockage(int i) {

    }

    void DefReader::add_def_placement_blockage(std::vector<std::vector<int> > const &vector) {

    }

    void readDef(std::string const &fileName, RawDataBase &db) {
        DefReader reader = DefReader(db);
        DefParser::read(reader, fileName.c_str());
        //db = reader.getRawDb();
        /// Sort region array and set Index
        /*std::sort(db.getRegionArray().begin(), db.getRegionArray().end());
        for (int i = 0; i < db.getRegionArray().size(); ++i) {
            db.getRegionArray()[i].setRegionIndex(static_cast<IndexType>(i));
        }
        std::sort(db.getRowArray().begin(), db.getRowArray().end());*/
        //db.setSiteWidth(db.getRowArray()[0].step[0]); /// site width defined by row
    }

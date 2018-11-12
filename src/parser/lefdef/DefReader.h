//
// Created by keren on 9/22/17.
//

#ifndef _DEFREADER_H
#define _DEFREADER_H


#include "DefDriver.h"
#include <algorithm>
#include "RawDataBase.h"
#include "DefReader.h"


    class DefReader : public DefParser::DefDataBase {


    public:
        /*
         * Constructor
         */


        explicit DefReader(RawDataBase &db)
                : _db(db) {

        }

        /*
         * Overrided functions
         */
    public:
        void set_def_dividerchar(const std::string &string) override;

        void set_def_busbitchars(const std::string &string) override;

        void set_def_version(const std::string &string) override;

        void set_def_design(const std::string &string) override;

        void set_def_unit(int i) override;

        void set_def_diearea(int i, int i1, int i2, int i3) override;

        void add_def_row(const DefParser::Row &row) override;

        void add_def_component(const DefParser::Component &component) override;

        void resize_def_component(int i) override;

        void add_def_pin(const DefParser::Pin &pin) override;

        void resize_def_pin(int i) override;

        void add_def_net(const DefParser::Net &net) override;

        void resize_def_net(int i) override;

        void add_def_track(const DefParser::Track &track) override;

        void add_def_snetpath(const DefParser::Snetp &snetp) override;

        void add_def_region(const DefParser::Region &region) override;

        void add_def_group(const DefParser::Group &group) override;

        void add_def_via(const DefParser::Via &via) override;

        void end_def_design() override;

        void resize_def_blockage(int i) override;

        void add_def_placement_blockage(std::vector<std::vector<int> > const &vector) override;

        RawDataBase &getRawDb() {
            return _db;
        }

    private:
        RawDataBase &_db;
    };

    void readDef(std::string const &fileName, RawDataBase &db);

#endif //_DEFREADER_H

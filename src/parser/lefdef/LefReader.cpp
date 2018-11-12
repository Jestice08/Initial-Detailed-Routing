
//
// Created by keren on 9/23/17.
//

#include "LefReader.h"
#define  IndexType std::uint32_t
#define  IntType std::int32_t
#define  RealType double

    void LefReader::lef_version_cbk(const std::string &v) {
    _db.setVersion(v);
    }

    void LefReader::lef_version_cbk(double v) {

    }

    void LefReader::lef_dividerchar_cbk(const std::string &v) {
    _db.setDivideChar(v);
    }

    void LefReader::lef_casesensitive_cbk(int v) {

    }

    void LefReader::lef_nowireextension_cbk(const std::string &v) {

    }

    void LefReader::lef_manufacturing_cbk(double v) {
    _db.setManufacturingGrid(v);
    }

    void LefReader::lef_useminspacing_cbk(lefiUseMinSpacing const &v) {

    }

    void LefReader::lef_clearancemeasure_cbk(const std::string &v) {
    _db.setClearanceMeasure(v);
    }

    void LefReader::lef_units_cbk(lefiUnits const &v) {
      Unit temp = Unit();
      //_db.units() = LefUnit();
      //auto &units = _db.units();
      if (v.hasDatabase())
      {
          temp.hasCapacitance = true;
          temp.databaseName = v.databaseName();
          temp.databaseNumber = v.databaseNumber();
          //units.hasDatabase = true;
          //units.databaseName = v.databaseName();
          //units.databaseNumber = v.databaseNumber();
      }
      if (v.hasCapacitance())
      {
          temp.hasCapacitance = true;
          temp.capacitance = v.capacitance();
          //units.hasCapacitance = true;
          //units.capacitance = v.capacitance();
      }
      if (v.hasPower())
      {
          temp.haspower = true;
          temp.power = v.power();
          //units.hasPower = true;
          //units.power = v.power();
      }
      _db.addUnitArray(temp);
    }

    void LefReader::lef_busbitchars_cbk(const std::string &v) {
    _db.setBusBitChars(v);
    }

    void LefReader::lef_layer_cbk(lefiLayer const &v) {
      if (v.hasType())
      {
          if (std::string(v.type()) == "CUT")
          {
              IndexType cutIdx = parseCutLayer(v);
              //_db.mapLayerStr2Idx()[v.name()] = _db.layerTypeVec().size();
              //_db.layerTypeVec().emplace_back(std::make_pair(0, cutIdx));
              return;
          }
          if (std::string(v.type()) == "ROUTING")
          {
              IndexType routingIdx = parseRoutingLayer(v);
              //_db.mapLayerStr2Idx()[v.name()] = _db.layerTypeVec().size();
              //_db.mapLayerStr2AccessIdx()[v.name()] = _db.accessLayerTypeVec().size();
            //  _db.layerTypeVec().emplace_back(std::make_pair(1, routingIdx));
              //DBG("%s: access %d %s \n", __FUNCTION__, _db.accessLayerTypeVec().size(), v.name());
              //_db.accessLayerTypeVec().emplace_back(std::make_pair(1, routingIdx));
              return;
          }
          if (std::string(v.type()) == "OVERLAP")
          {
              parseOverlapLayer(v);
              //_db.mapLayerStr2Idx()[v.name()] = _db.layerTypeVec().size();
              //_db.layerTypeVec().emplace_back(std::make_pair(3, 0));
              //INF("%s: ignore OVERLAP layer %s. Not influence routing\n", __FUNCTION__, v.name());
              return;
          }
          //AssertMsg(false, "%s: unknown layer type %s \n", __FUNCTION__, v.type());
      }
      else
      {
          //AssertMsg(false, "%s: layer does not have type!\n", __FUNCTION__);
      }
    }

    void LefReader::lef_maxstackvia_cbk(lefiMaxStackVia const &v) {

    }

    void LefReader::lef_via_cbk(lefiVia const &v) {
      if (v.hasGenerated())
      {
      }
      else
      {
          parseFixedVia(v);
      }
    }

    void LefReader::lef_viarule_cbk(lefiViaRule const &v) {

    }

    void LefReader::lef_spacing_cbk(lefiSpacing const &v) {

    }

    void LefReader::lef_irdrop_cbk(lefiIRDrop const &v) {

    }

    void LefReader::lef_minfeature_cbk(lefiMinFeature const &v) {

    }

    void LefReader::lef_dielectric_cbk(double v) {

    }

    void LefReader::lef_nondefault_cbk(lefiNonDefault const &v) {

    }

    void LefReader::lef_site_cbk(lefiSite const &v) {
        if (v.hasSize()) {
            _db.setLefSiteSizeX(v.sizeX());
            _db.setLefSiteSizeY(v.sizeY());
        } else {
            assert(false);
        }
    }

    void LefReader::lef_macrobegin_cbk(std::string const &v) {
        /// For pin parsering
        //lef_macrobegin_cbk(v);
        //std::cout<<v<<std::endl;
        currentMacroName = v;
        StdCell temp = StdCell();
        temp.setMacroName(currentMacroName);
        _db.addStdCellLib( temp);
    }

    void LefReader::lef_macro_cbk(lefiMacro const &v) {
        //LefDataBase::lef_macro_cbk(v);
        assert(v.hasXSymmetry());
        assert(v.hasYSymmetry());
        assert(v.originX() == 0 && v.originY() == 0);
        _db.getStdCellLib(currentMacroName).setSizeX(v.sizeX());
        _db.getStdCellLib(currentMacroName).setSizeY(v.sizeY());

        /// Process the string for extracting the edgetype information
        bool left = true;
        bool right = true;
        bool hasedge = false;
        IndexType property_num = static_cast<IndexType>(v.numProperties());
        std::string property_value;
        for (IndexType i = 0; i < property_num; ++i) {
            //cout<<"Index: "<<i<< " Property name:"<<v.propName(i)<<" Property value: "<< v.propValue(i)<<endl;
            property_value = v.propValue(i);
            size_t found = property_value.find("EDGETYPE");
            if (found != std::string::npos)
                hasedge = true;
            while (found != std::string::npos) {
                property_value = property_value.substr(found + 8, property_value.length());
                size_t indi = property_value.find(" ");
                if (property_value.substr(indi + 1, indi + 4) == "LEFT") {

                    if (property_value[indi + 6] == '2')
                        left = true;
                    else
                        left = false;
                } else if (property_value.substr(indi + 1, indi + 5) == "RIGHT") {
                    if (property_value[indi + 7] == '2')
                        right = true;
                    else
                        right = false;
                }
                found = property_value.find("EDGETYPE");


            }
            assert(hasedge);
            if (hasedge) {
                if (left) {
                    _db.getStdCellLib(currentMacroName).setEdgeLeft(2);
                }
                else {
                    _db.getStdCellLib(currentMacroName).setEdgeLeft(1);
                }
                if (right) {
                    _db.getStdCellLib(currentMacroName).setEdgeRight(2);
                }
                else {
                    _db.getStdCellLib(currentMacroName).setEdgeRight(1);
                }

            }

        }

    }

    void LefReader::lef_macro_endcbk(const char *macroName) {
        //LefDataBase::lef_macro_endcbk(macroName);
        /*
        std::cout<< _db.getStdCellLib()[currentMacroName].getMacroName()<<std::endl;
        std::cout<<_db.getStdCellLib()[currentMacroName].getSizeX()<<" "<<_db.getStdCellLib()[currentMacroName].getSizeY()<<std::endl;
        for (auto const &pin : _db.getStdCellLib()[currentMacroName].getPins()) {
            std::cout<<pin.xLo()<<" "<<pin.yLo()<<" "<<pin.xHi()<<" "<<pin.yHi()<<std::endl;
        }
        */
    }

    void LefReader::lef_pin_cbk(lefiPin const &v) {

        //LefDataBase::lef_pin_cbk(v);
        //std::cout<<v.name()<<std::endl;
        std::string str = std::string(v.name());
        if (str == "vdd") {
            for (IndexType portIndex = 0; portIndex < v.numPorts(); ++portIndex) {
                //lefiGeometries test = *v.port(portIndex);
                for (IndexType geoIndex = 0; geoIndex < v.port(portIndex)->numItems(); ++geoIndex) {
                    if (v.port(portIndex)->itemType(geoIndex) == lefiGeomRectE) {
                        if (v.port(portIndex)->getRect(geoIndex)->yh < 0.5) {
                            _db.getStdCellLib(currentMacroName).setBottomVss(false);
                            //std::cout<<currentMacroName<<" vdd"<<std::endl;
                            break;
                        }
                    }
                }

            }
        } else if (str == "vss") {
            for (IndexType portIndex = 0; portIndex < v.numPorts(); ++portIndex) {
                //lefiGeometries test = *v.port(portIndex);
                for (IndexType geoIndex = 0; geoIndex < v.port(portIndex)->numItems(); ++geoIndex) {
                    if (v.port(portIndex)->itemType(geoIndex) == lefiGeomRectE) {
                        if (v.port(portIndex)->getRect(geoIndex)->yh < 0.5) {
                            _db.getStdCellLib(currentMacroName).setBottomVss(true);
                            //std::cout<<currentMacroName<<" vss"<<std::endl;
                            break;
                        }
                    }
                }

            }
        } else {
            for (IndexType portIndex = 0; portIndex < v.numPorts(); ++portIndex) {
                //lefiGeometries test = *v.port(portIndex);
                for (IndexType geoIndex = 0; geoIndex < v.port(portIndex)->numItems(); ++geoIndex) {
                    if (v.port(portIndex)->itemType(geoIndex) == lefiGeomRectE) {
                        _db.getStdCellLib(currentMacroName).addPin(
                                v.port(portIndex)->getRect(geoIndex)->xl,
                                v.port(portIndex)->getRect(geoIndex)->yl,
                                v.port(portIndex)->getRect(geoIndex)->xh,
                                v.port(portIndex)->getRect(geoIndex)->yh,
								v.name()
                        );
                        //_db.getStdCellLib(currentMacroName).addPinName(v.name());
                    }


                }

            }

        }

    }

    void LefReader::lef_obstruction_cbk(lefiObstruction const &v) {

    }

    void LefReader::lef_density_cbk(lefiDensity const &v) {

    }

    void LefReader::lef_timing_cbk(lefiTiming const &v) {

    }

    void LefReader::lef_array_cbk(lefiArray const &v) {

    }

    void LefReader::lef_prop_cbk(lefiProp const &v) {
/*
        std::string spacingkwd = "CELLEDGESPACINGTABLE";
        std::string edgetpkwd = "EDGETYPE";
        if (v.hasString()) {
            std::vector<std::string> vt;
            std::string s = v.string();
            boost::algorithm::split(vt, s, boost::algorithm::is_space());
            for (int i = 0; i < vt.size(); ++i) {
                if (boost::iequals(vt[i], spacingkwd)) {

                }
                if (boost::iequals(vt[i], edgetpkwd)) {
                    if (vt[i + 1] == "2" && vt[i + 2] == "1") {
                        _db.setLefEdgeSpacing12(atof(vt[i + 3].c_str()));
                    } else if (vt[i + 1] == "1" && vt[i + 2] == "2") {
                        _db.setLefEdgeSpacing12(atof(vt[i + 3].c_str()));
                    } else if (vt[i + 1] == "2" && vt[i + 2] == "2") {
                        _db.setLefEdgeSpacing22(atof(vt[i + 3].c_str()));
                    } else if (vt[i + 1] == "1" && vt[i + 2] == "1") {
                        _db.setLefEdgeSpacing11(atof(vt[i + 3].c_str()));
                    }

                }

            }
        }
    */
    }

    void LefReader::lef_noisemargin_cbk(lefiNoiseMargin const &v) {

    }

    void LefReader::lef_edgeratethreshold1_cbk(double v) {

    }

    void LefReader::lef_edgeratethreshold2_cbk(double v) {

    }

    void LefReader::lef_edgeratescalefactor_cbk(double v) {

    }

    void LefReader::lef_noisetable_cbk(lefiNoiseTable const &v) {

    }

    void LefReader::lef_correctiontable_cbk(lefiCorrectionTable const &v) {

    }

    void LefReader::lef_inputantenna_cbk(double v) {

    }

    void LefReader::lef_outputantenna_cbk(double v) {

    }

    void LefReader::lef_inoutantenna_cbk(double v) {

    }

    void LefReader::lef_antennainput_cbk(double v) {

    }

    void LefReader::lef_antennaoutput_cbk(double v) {

    }

    void LefReader::lef_antennainout_cbk(double v) {

    }

    void LefReader::lef_extension_cbk(const std::string &v) {

    }

    IndexType LefReader::parseCutLayer(lefiLayer const &v)
    {
        LefLayerCut cut = LefLayerCut();
        cut.name = std::string(v.name());
        cut.width = v.width();
        //what's v.spacing?
        IntType numSpacing = v.numSpacing();
        /// TODO: Handle other spacings
        for (IntType spacingIdx = 0; spacingIdx < numSpacing; ++ spacingIdx)
        {
            //cut.spacing = v.spacing(spacingIdx);
            cut.spacing = v.spacing(0);
        }
        /// Return index of this in the cut layers
        IndexType cutIdx = _db.cutLayers().size();
        _db.cutLayers().emplace_back(cut);
        return cutIdx;
    }

    IndexType LefReader::parseRoutingLayer(lefiLayer &v)
    {
        LefLayerRouting route = LefLayerRouting();

        route.name = std::string(v.name());
        if (v.hasPitch())
        {
            route.hasPitch = true;
            route.pitch = v.pitch();
        }
        if (v.hasXYPitch())
        {
            route.hasXYPitch = true;
            route.pitchX = v.pitchX();
            route.pitchY = v.pitchY();
        }
      /*if (v.hasOffset())
        {
            route.hasOffset = true;
            route.offset = v.offset();
        }
        if (v.hasXYOffset())
        {
            route.hasXYOffset = true;
            route.offsetX = v.offsetX();
            route.offsetY = v.offsetY();
        }*/
        if (v.hasWidth())
        {
            route.hasWidth = true;
            route.width = v.width();
        }
        if (v.hasArea())
        {
            route.hasArea = true;
            route.area = v.area();
        }
        if (v.hasSpacingNumber())
        {
            route.hasSpacingNumber = true;
            route.numSpacing = v.numSpacing();
        }
        /// Process spacing information in other subroutine
        for (IntType idx = 0; idx < route.numSpacing; ++idx)
        {
            processRoutingLayerSpacing(route, v, idx);//can't understand
        }

        if (v.hasDirection())
        {
            route.hasDirection = true;
            route.direction = std::string(v.direction());
        }
        if (v.hasMinwidth())
        {
            route.hasMinWidth = true;
            route.minWidth = v.minwidth();
        }
        if (v.hasMaxwidth())
        {
            route.hasMaxWidth = true;
            route.maxWidth = v.maxwidth();
        }

        ///spacing table
        route.numSpacingTable = v.numSpacingTable();

        for (IntType idx = 0; idx < route.numSpacingTable; ++idx)
        {
            const auto &spTable = v.spacingTable(idx);
            if (spTable->isParallel())
            {
                processRoutingLayerSpacingTableParallel(route, spTable);
            }
            else if (spTable->isInfluence())
            {
                AssertMsg(false, "%s: expect no influence \n", __FUNCTION__);
            }
            /// Spacingtable can only be influence, parallel, and twoWidth
            else
            {
                for (IntType twoWidthIdx = 0; twoWidthIdx < spTable->twoWidths()->numWidth(); ++twoWidthIdx)
                {
                    DBG("%s: layer %s twoWidth %d/%d: %d\n", __FUNCTION__, v.name(), twoWidthIdx, spTable->twoWidths()->numWidth(), spTable->twoWidths()->width(twoWidthIdx));
                }
            }
            /// twoWidth
        }

        ///Return the index of the input in the routing layers
        IndexType routingIdx = _db.routingLayers().size();
        _db.routingLayers().emplace_back(route);
        return routingIdx;
    }

    void LefReader::parseOverlapLayer(lefiLayer const &v)
    {
        LefLayerOverlap overlap = LefLayerOverlap();
        overlap.name = std::string(v.name());
        /*cut.width = v.width();
        //what's v.spacing?
        IntType numSpacing = v.numSpacing();
        /// TODO: Handle other spacings
        for (IntType spacingIdx = 0; spacingIdx < numSpacing; ++ spacingIdx)
        {
            //cut.spacing = v.spacing(spacingIdx);
            cut.spacing = v.spacing(0);
        }
        /// Return index of this in the cut layers
        IndexType cutIdx = _db.cutLayers().size();
        _db.cutLayers().emplace_back(cut);
        return cutIdx;*/
        _db.overlapLayers().emplace_back(overlap);
    }

    void LefReader::processRoutingLayerSpacing(LefLayerRouting &route, lefiLayer const &v, IntType spacingIdx)
    {
        if (v.hasSpacingName(spacingIdx))
        {
        }
        else if (v.hasSpacingLayerStack(spacingIdx))
        {
        }
        else if (v.hasSpacingAdjacent(spacingIdx))
        {
        }
        else if (v.hasSpacingCenterToCenter(spacingIdx))
        {
        }
        /// add others later... if not forever...
        else if (v.hasSpacingEndOfLine(spacingIdx))
        {
            EolSpacing temp = EolSpacing();
            temp.spacing = v.spacing(spacingIdx);
            temp.spacingEolWidth = v.spacingEolWidth(spacingIdx);
            temp.spacingEolWithin = v.spacingEolWithin(spacingIdx);
            route.addEolSpacingArray().emplace_back(temp);
            //route.eolSpacing.emplace_back(EOLSpacing(v.spacing(spacingIdx), v.spacingEolWidth(spacingIdx), v.spacingEolWithin(spacingIdx)));
        }
        /// others...
        else
        {
            /// raw spacing...
            route.addSpacingArray().emplace_back(v.spacing(spacingIdx));
        }
    }

    void LefReader::processRoutingLayerSpacingTableParallel(LefLayerRouting &route, lefiSpacingTable const *v)
    {
        const lefiParallel *para = v->parallel();
        SpacingTable temp = SpacingTable();
        for (IntType lenIdx = 0; lenIdx < para->numLength(); ++lenIdx)
        {
            temp.spacingTableParallelRunLength.emplace_back(para->length(lenIdx));
        }
        for (IntType widthIdx = 0; widthIdx < para->numWidth(); ++widthIdx)
        {
            temp.spacingTableWidth.emplace_back(para->width(widthIdx));
        }
        //route.spacingTableSpacing.resize(para->numLength(), para->numWidth());
        //temp.spacingTableSpacing.resize(para->numWidth());
        for (IntType lenIdx = 0; lenIdx < para->numLength(); ++lenIdx) //assume length = 1
        {
            for (IntType widthIdx = 0; widthIdx < para->numWidth(); ++widthIdx)
            {
                temp.spacingTableSpacing.emplace_back(para->widthSpacing(widthIdx, lenIdx));
                //route.spacingTableSpacing.at(lenIdx, widthIdx) = para->widthSpacing(widthIdx, lenIdx);
            }
        }
        route.spacingTableArray.emplace_back(temp);
    }

    IndexType LefReader::parseMastersliceLayer(const lefiLayer &v)
    {
        LefLayerMasterslice masterslice = LefLayerMasterslice();

        masterslice.name = v.name();
        IndexType masterIdx = _techDB.mastersliceLayers().size();
        _techDB.mastersliceLayers().emplace_back(masterslice);
        return masterIdx;
    }

    /// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    ///Via

    void LefReader::parseFixedVia(const lefiVia &v)
    {
        LefRawFixedVia via = LefRawFixedVia();
        via.name = v.name();
        if (v.hasDefault())
        {
            via.isDefault = true;
        }
        if (v.hasResistance())
        {
            via.hasResistance = true;
            via.resistance = v.resistance();
        }

        /// bottom, cut, top
        AssertMsg(v.numLayers() == 3, "%s: VIA %s does not exactly have three layers, which is the default assumption. Instead, having %d \n", __FUNCTION__, v.name(), v.numLayers());

        RealType xLo = 0;
        RealType yLo = 0;
        RealType xHi = 0;
        RealType yHi = 0;

        /// Bottom
        via.bottomLayer = v.layerName(0);
        AssertMsg(v.numRects(0) == 1, "%s: VIA %s bottom layer does not have exactly one rectangle! \n", __FUNCTION__, v.name());
        AssertMsg(v.numPolygons(0) == 0, "%s, VIA %s bottom layer has polygons! \n", __FUNCTION__, v.name());
        xLo = v.xl(0, 0);
        yLo = v.yl(0, 0);
        xHi = v.xh(0, 0);
        yHi = v.yh(0, 0);
        via.bottomLayerRect[0] = xLo;
        via.bottomLayerRect[1] = yLo;
        via.bottomLayerRect[2] = xHi;
        via.bottomLayerRect[3] = yHi;
        //via.bottomLayerRect = Box<RealType>(xLo, yLo, xHi, yHi);

        /// CUT
        via.cutLayer = v.layerName(1);
        AssertMsg(v.numRects(1) > 0, "%s: VIA %s cut layer does not have rectangle! \n", __FUNCTION__, v.name());
        AssertMsg(v.numPolygons(1) == 0, "%s, VIA %s cut layer has polygons! \n", __FUNCTION__, v.name());
        IntType numCut = v.numRects(1);
        via.numCutRect = static_cast<IndexType>(numCut);
        via.cutLayerRectArray.resize(0);
        via.cutLayerRectArray.reserve(numCut);
        for (IntType cutRectIdx = 0; cutRectIdx < numCut; ++cutRectIdx)
        {
            xLo = v.xl(1, cutRectIdx);
            yLo = v.yl(1, cutRectIdx);
            xHi = v.xh(1, cutRectIdx);
            yHi = v.yh(1, cutRectIdx);
            cutLayerRect temp = cutLayerRect();
            temp.rect[0] = xLo;
            temp.rect[1] = yLo;
            temp.rect[2] = xLi;
            temp.rect[3] = yLi;
            via.cutLayerRectArray.emplace_back(temp);
            //via.cutLayerRectArray.emplace_back(Box<RealType>(xLo, yLo, xHi, yHi));
        }

        /// top
        via.topLayer = v.layerName(2);
        AssertMsg(v.numRects(2) == 1, "%s: VIA %s top layer does not have exactly one rectangle! \n", __FUNCTION__, v.name());
        AssertMsg(v.numPolygons(2) == 0, "%s, VIA %s top layer has polygons! \n", __FUNCTION__, v.name());
        xLo = v.xl(2, 0);
        yLo = v.yl(2, 0);
        xHi = v.xh(2, 0);
        yHi = v.yh(2, 0);
        via.topLayerRect[0] = xLo;
        via.topLayerRect[1] = yLo;
        via.topLayerRect[2] = xHi;
        via.topLayerRect[3] = yHi;
        //via.topLayerRect = Box<RealType>(xLo, yLo, xHi, yHi);

        _db.fixedVias().emplace_back(via);
    }

    ////////////////////
    /// Post processing
    ////////////////////

    /// Wrapper function
/*
    void LefReader::postProcessing()
    {
        /// Fixed VIA
        _macroDB.fixedViaVec2D().resize(_techDB.accessLayerTypeVec().size());
        for (const auto &rawVia : _rawFixedViaArray)
        {
            postProcessFixedVia(rawVia);
        }
        /// Sort Vias to put the default vias in the end
        auto func = [&](LefFixedVia via1, LefFixedVia via2)
        {
            if (via1.isDefault())
                return true;
            else if (via2.isDefault())
                return false;
            else
                return true;
        };
        for (auto &fixedViaVec : _macroDB.fixedViaVec2D())
        {
            std::stable_sort(fixedViaVec.begin(), fixedViaVec.end(), func);
            for (auto &fixedVia : fixedViaVec)
            {
                fixedVia.findBoundingBox();
            }
        }
    }

    void LefReader::postProcessFixedVia(const LefRawFixedVia &rawVia)
    {
        LefFixedVia via;
        via.setName(rawVia.name);
        via.setIsDefault(rawVia.isDefault);
        via.setHasResistance(rawVia.hasResistance);
        via.setResistance(klib::round2Int(RESISTANCE_PRECISION * rawVia.resistance));

        /// Get the correct index based on name
        AssertMsg(_techDB.mapLayerStr2AccessIdx().find(rawVia.bottomLayer) != _techDB.mapLayerStr2AccessIdx().end(), "%s: via %s bottom %s top %s \n", __FUNCTION__, rawVia.name.c_str(), rawVia.bottomLayer.c_str(), rawVia.topLayer.c_str());
        AssertMsg(_techDB.mapLayerStr2AccessIdx().find(rawVia.topLayer) != _techDB.mapLayerStr2AccessIdx().end() || \
                _techDB.layerTypeVec()[_techDB.mapLayerStr2Idx()[rawVia.topLayer]].first == 3, "%s: via %s bottom %s top %s \n", __FUNCTION__, rawVia.name.c_str(), rawVia.bottomLayer.c_str(), rawVia.topLayer.c_str());
        AssertMsg(_techDB.mapLayerStr2AccessIdx()[rawVia.topLayer] - _techDB.mapLayerStr2AccessIdx()[rawVia.bottomLayer] == 1, "%s: via %s bottom %s top %s \n", __FUNCTION__, rawVia.name.c_str(), rawVia.bottomLayer.c_str(), rawVia.topLayer.c_str());
        via.setAccessLayerIdx(_techDB.mapLayerStr2AccessIdx()[rawVia.bottomLayer]);
        via.setBottomLayerIdx(_techDB.mapLayerStr2Idx()[rawVia.bottomLayer]);
        via.setCutLayerIdx(_techDB.mapLayerStr2Idx()[rawVia.cutLayer]);
        via.setTopLayerIdx(_techDB.mapLayerStr2Idx()[rawVia.topLayer]);

        /// Convert rect unit from um to databse unit
        LocType xLo;
        LocType yLo;
        LocType xHi;
        LocType yHi;

        /// Bottom
        xLo = static_cast<LocType>(rawVia.bottomLayerRect.xLo() * _techDB.units().databaseNumber);
        yLo = static_cast<LocType>(rawVia.bottomLayerRect.yLo() * _techDB.units().databaseNumber);
        xHi = static_cast<LocType>(rawVia.bottomLayerRect.xHi() * _techDB.units().databaseNumber);
        yHi = static_cast<LocType>(rawVia.bottomLayerRect.yHi() * _techDB.units().databaseNumber);
        via.bottomRect() = Box<LocType>(xLo, yLo, xHi, yHi);

        /// Cut
        via.setNumCutRect(rawVia.numCutRect);
        via.cutRectArray().resize(0);
        via.cutRectArray().reserve(rawVia.numCutRect);
        for (IndexType cutIdx = 0; cutIdx < via.numCutRect(); ++cutIdx)
        {
            xLo = static_cast<LocType>(rawVia.cutLayerRectArray.at(cutIdx).xLo() * _techDB.units().databaseNumber);
            yLo = static_cast<LocType>(rawVia.cutLayerRectArray.at(cutIdx).yLo() * _techDB.units().databaseNumber);
            xHi = static_cast<LocType>(rawVia.cutLayerRectArray.at(cutIdx).xHi() * _techDB.units().databaseNumber);
            yHi = static_cast<LocType>(rawVia.cutLayerRectArray.at(cutIdx).yHi() * _techDB.units().databaseNumber);
            via.cutRectArray().emplace_back(Box<LocType>(xLo, yLo, xHi, yHi));
        }

        /// Top
        xLo = static_cast<LocType>(rawVia.topLayerRect.xLo() * _techDB.units().databaseNumber);
        yLo = static_cast<LocType>(rawVia.topLayerRect.yLo() * _techDB.units().databaseNumber);
        xHi = static_cast<LocType>(rawVia.topLayerRect.xHi() * _techDB.units().databaseNumber);
        yHi = static_cast<LocType>(rawVia.topLayerRect.yHi() * _techDB.units().databaseNumber);
        via.topRect() = Box<LocType>(xLo, yLo, xHi, yHi);

        /// push_back to the vector
        _macroDB.fixedViaVec2D().at(via.accessLayerIdx()).emplace_back(via);
    }
*/

    void readLef(std::string const &fileName, MacroDataBase &db) {
        LefReader reader = LefReader(db);
        LefParser::read(reader, fileName.c_str());
        //db =reader.getDb();
    }

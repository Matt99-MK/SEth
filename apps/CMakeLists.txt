####### WxWidgets
set(wxWidgets_ROOT_DIR C:/wxWidgets-3.1.3)
find_package(wxWidgets REQUIRED COMPONENTS net core base gl xml aui html media propgrid qa ribbon richtext stc webview xrc)
include(${wxWidgets_USE_FILE})
######## WxWidgets

######## Poco
set(Poco_ALL_LIBRARIES "Poco::CppParser Poco::Crypto Poco::Encodings Poco::Foundation Poco:JSON Poco::MongoDB Poco::Net Poco::NetSSL Poco::NetSSLWin Poco::PDF Poco::Redis Poco::SQL Poco::SQLODBC Poco::SQLPostgreSQL Poco::SQLSQLite Poco::SevenZip Poco::Util Poco::XML Poco::Zip")
Set(Poco_LIBRARIES Poco::CppParser Poco::Crypto Poco::Encodings Poco::Foundation Poco::MongoDB Poco::Net Poco::Data Poco::NetSSL Poco::Redis Poco::DataODBC Poco::DataSQLite Poco::SevenZip Poco::Util Poco::XML Poco::Zip)
message("CMAKE_TOOLCHAIN_FILE : ${CMAKE_TOOLCHAIN_FILE}")
find_package(Poco CONFIG REQUIRED DataMySQL CppParser Data Crypto Encodings Foundation JSON MongoDB Net NetSSL Redis SevenZip Util XML Zip DataODBC DataSQLite)
######## Poco

######## Boost
find_package(Boost REQUIRED COMPONENTS random )
######## Boost

######## OpenCV
find_package( OpenCV REQUIRED )
######## OpenCV

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) Excluding from this folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

#Add library for Poco Database
add_library(PocoDatabase STATIC ../PocoDataBase/DataBaseConnection.cpp)
target_link_libraries(PocoDatabase ${Poco_LIBRARIES})
include_directories(../PocoDataBase/)

#Add network library
include_directories(../Network/)
add_definitions(-DWIN32_LEAN_AND_MEAN)

#1
include_directories(include_apps/)
link_directories(../libs)
add_executable(SEth "source_apps/MainWindow.cpp" "source_apps/MainApp.cpp" "source_apps/Utils.cpp"
"source_apps/UserImage.cpp" "source_apps/MenuButton.cpp" "source_apps/SearchWindow.cpp"  "source_apps/ColumnRender.cpp"
"source_apps/AppList.cpp" "source_apps/UserModelData.cpp"  "source_apps/MainXmlDocument.cpp" "source_apps/AddUserButton.cpp"
"source_apps/ScrolledPanel.cpp" "source_apps/MainSearchCtrl.cpp" ../Resource_Files/Resource.rc "../Network/DenyFilter.cpp"
"../Network/Session.cpp" )


SET_TARGET_PROPERTIES (SEth PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:windows")
target_link_libraries(SEth ${wxWidgets_LIBRARIES} ${Poco_LIBRARIES}  ${Boost_LIBRARIES} ${OpenCV_LIBS} PocoDatabase)

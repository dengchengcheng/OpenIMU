#include "testpipeline.h"

#include "../../application_openimu/app/models/caneva.h"
#include "../../application_openimu/app/models/components/block.h"
#include "../../application_openimu/app/models/components/inputnode.h"
#include "../../application_openimu/app/models/components/outputnode.h"
#include "../../application_openimu/app/models/json/json/json.h"

TestPipeline::TestPipeline(QObject *parent) : QObject(parent)
{

}

void TestPipeline::testsJSON()
{
    QFETCH(Json::Value, layout);
    QFETCH(QString, string);
    QFETCH(QString, result);



    QCOMPARE(string.toUpper(),result);
}

void TestPipeline::testsJSON_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("result");
    QTest::addColumn<QString>("result");

    QTest::newRow("all lower") << "hello" << "HELLO";
    QTest::newRow("mixed")     << "Hello" << "HELLO";
    QTest::newRow("all upper") << "HELLO" << "HELLO";
}

# include <QString>
# include <QTest>
# include <random>
# include <string>
# include "settings.h"
class SettingsTest : public QObject
{
   Q_OBJECT

   public :
   SettingsTest() {}

   private Q_SLOTS :
   void TestsOfInit()
   {
       settings test1("config.ini");
       test1.reset();
       test1.reload();
   }

   void TestsOfSettingAndGetting()
   {
       settings test1("config.ini");

       test1.set("fst", "snd");
       QCOMPARE(test1.get("fst"), string("snd"));

       test1.set("fst", "fst");
       QCOMPARE(test1.get("fst"), string("fst"));

       QCOMPARE(test1.get("new", string("new1")), string("new1"));

       test1.reset();
   }

   void TestsOfInt()
   {
       settings test1("config.ini");

       test1.set("fst" , "val1~@345434EDTFRJS");
       test1.set("snd", "true");
       test1.set("trd", "2324");
       test1.set("dbl", "76.3");

       QCOMPARE((string)test1.get("fst"), string("val1~@345434EDTFRJS"));
       QCOMPARE((string)test1.get("snd"), string("true"));
       QCOMPARE((string)test1.get("trd"), string("2324"));
       QCOMPARE((string)test1.get("dbl"), string("76.3"));

       QVERIFY_EXCEPTION_THROWN(int y = stoi(test1.get("fst")), std::invalid_argument);
       QVERIFY_EXCEPTION_THROWN(int y = stoi(test1.get("snd")), std::invalid_argument);
       int tmp = stoi(test1.get("trd"));
       QCOMPARE(tmp, 2324);
       int tmp1 = stoi(test1.get("dbl"));
       QCOMPARE(tmp1, (int)76.3);

       //Checking All operators
       int a = stoi(test1.get("trd"));
       QCOMPARE(a += 5, 2324+5);
       QCOMPARE(a -= 5, 2324);
       QCOMPARE(a *= 5, 2324*5);
       QCOMPARE(a /= 5, 2324);

       int b = stoi(test1.get("dbl"));
       QCOMPARE(b += 2, 76+2);
       QCOMPARE(b -= 2, 76);
       QCOMPARE(b *= 2, 76*2);
       QCOMPARE(b /= 2, 76);

       // Deleting
       test1.reset();
   }

   void TestsOfDouble()
   {
       settings test1("config.ini");

       test1.set("fst" , "val1~@345TFRJS");
       test1.set("snd", "false");
       test1.set("trd", "12");
       test1.set("dbl", "76.3");

       QCOMPARE((string)test1.get("fst"), string("val1~@345TFRJS"));
       QCOMPARE((string)test1.get("snd"), string("false"));
       QCOMPARE((string)test1.get("trd"), string("12"));
       QCOMPARE((string)test1.get("dbl"), string("76.3"));

       QVERIFY_EXCEPTION_THROWN(double y = stod(test1.get("fst")), std::invalid_argument);
       QVERIFY_EXCEPTION_THROWN(double y = stod(test1.get("snd")), std::invalid_argument);
       double tmp = stod(test1.get("trd"));
       QCOMPARE(tmp, double(12));
       double tmp1 = stod(test1.get("dbl"));
       QCOMPARE(tmp1, 76.3);

       //Checking All operators
       double a = stod(test1.get("trd"));
       QCOMPARE(a += 1.1, double(12+1.1));
       QCOMPARE(a -= 1.1, double(12));
       QCOMPARE(a *= 1, double(12));
       QCOMPARE(a /= 1, double(12));

       double b = stod(test1.get("dbl"));
       QCOMPARE(b += 0.7, double(77));
       QCOMPARE(b -= 0.7, double(76.3));
       QCOMPARE(b *= 1.5, 76.3*(1.5));
       QCOMPARE(b /= 1.5, 76.3);

       // Deleting
       test1.reset();
   }

   void bigTestWithReload()
   {
       settings test1("config.ini");
       for (int i = 0; i < 1500; ++i)
       {
           test1.set("test number: " + to_string(i), to_string(i));
           QCOMPARE(test1.get("test number: " + to_string(i)), to_string(i));
       }
       test1.reload();
       for (int i = 0; i < 1500; ++i)
       {
           QCOMPARE(test1.get("test number: " + to_string(i)), to_string(i));
       }
       test1.reset();
       for (int i = 0; i < 1500; ++i)
       {
           QCOMPARE(test1.get("test number: " + to_string(i)), string(""));
       }


   }

   void TestsWithRandom()
   {
       settings test1("config.ini");
       mt19937_64 rnd;
       long long nums[50];
       for (int i = 0; i < 50; ++i)
       {
           nums[i] = rnd();
           test1.set("random number: " + to_string(i), to_string(nums[i]));
           QCOMPARE(test1.get("random number: " + to_string(i)), to_string(nums[i]));
       }
   }

   void TestsWithFewFiles()
   {
       settings test1("config1.ini"),
                test2("config2.ini"),
                test3("config3.ini"),
                test4("config4.ini");

       test1.set("filename", "a");
       test2.set("filename", "b");
       test3.set("filename", "c");
       test4.set("filename", "d");

       QCOMPARE(test1.get("filename"), string("a"));
       QCOMPARE(test2.get("filename"), string("b"));
       QCOMPARE(test3.get("filename"), string("c"));
       QCOMPARE(test4.get("filename"), string("d"));

       test1.reset();
       test2.reset();
       test3.reset();
       test4.reset();
   }

   void TestWithObjectsInOnePlace()
   {
       settings test1("config.ini");
       settings test2("config.ini");
       //set q in last for test1
       test1.set("last", "q");
       QCOMPARE(test1.get("last"), string("q"));

       if(test2.get("last") == "")
       cout << "       : Nothing, because no reloading in test2" << endl;

       //now we set q in last for test2 with reloading, because they in one place
       test2.reload();
       QCOMPARE(test2.get("last"), string("q"));

       //now we delete everything in test2 (and in test1 automatically)
       test2.reset();
       test1.reload();
       QCOMPARE(test1.get("last"), string(""));
       QCOMPARE(test2.get("last"), string(""));

       //now we set newTmp in newPlace for test1 and after reload test2
       test1.set("newPlace","newTmp");
       test2.reload();
       QCOMPARE(test2.get("newPlace"),string("newTmp"));
   }
};
QTEST_APPLESS_MAIN(SettingsTest);

#include "settingsTest.moc"

#include "C_data.h"


//
// Konstruktor
// ----------------------------------------------------------------------------------------------------------------------------------
//
C_dat::C_dat()
{

    // Anfangswerte setzen
    eventnumber = 0;
    nexteventnumber = 0;
    previouseventnumber = 0;

    tracknumber = -1;
    m_normfaktor = 50;

    m_file = new QFile();

    number_event_search = 100;

    trigger_value = 1;
    maximum_value = 1;
    active_fibers = 1;

    // Auslesen des Dateipfades aus path.txt. path.txt muss im gleichen Ordner liegen, wie exe-Datei
    QFile file("path.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line = in.readLine();           // Text (=Dateipfad) wird in line eingelesen
    eventdirection = line;                  // eventdirection wird der Pfad zugewiesen, in welchem die Eventdateien liegen


    // Arrays mit Anfangswertenbelegen
    for (int i=0; i<15;i++)
    {
        for (int j=0; j<30;j++)
        {
            xzArray[j][i] = 0;
            yzArray[j][i] = 0;
        }
    }


}
// ----------------------------------------------------------------------------------------------------------------------------------
// Konstruktor ENDE


//
// get_active_fibers
// ----------------------------------------------------------------------------------------------------------------------------------
//
int C_dat::get_active_fibers()
{
    return active_fibers;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// get_active_fibers ENDE


//
// get_maximum_value
// ----------------------------------------------------------------------------------------------------------------------------------
//
int C_dat::get_maximum_value()
{
    return maximum_value;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// get_maximum_value ENDE


//
// get_trigger_value
// ----------------------------------------------------------------------------------------------------------------------------------
//
int C_dat::get_trigger_value()
{
    return trigger_value;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// get_trigger_value ENDE


//
// open_number
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_dat::open_number(int number)
{
    // Bekommt Eventnummer uebergeben, an die gesprungen werden soll. eventnumber wird dann gleich dieser Nummer gesetzt
    eventnumber = number;
    // Es wird ueberprueft, ob es zu dieser nummer ein naechstes Event gibt
    isnext();
    // Es wird zum naechsten Event gegangen
    next();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// open_number ENDE


//
// getEventnumber
// ----------------------------------------------------------------------------------------------------------------------------------
//
int C_dat::getEventnumber()
{
    return eventnumber;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// getEventnumber ENDE


//
// getTracksize
// ----------------------------------------------------------------------------------------------------------------------------------
//
int C_dat::getTrackSize()
{
    return trackpositions.size();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// getTracksize ENDE


//
// gettracknumber
// ----------------------------------------------------------------------------------------------------------------------------------
//
int C_dat::gettracknumber()
{
    return tracknumber;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// gettracknumber ENDE


//
// getTrackStartPos
// ----------------------------------------------------------------------------------------------------------------------------------
//
QVector3D C_dat::getTrackStartPos(int track)
{
        return trackpositions.at(track).at(0);
}
// ----------------------------------------------------------------------------------------------------------------------------------
// getTrackStartPos ENDE


//
// getTrackEndPos
// ----------------------------------------------------------------------------------------------------------------------------------
//
QVector3D C_dat::getTrackEndPos(int track)
{
        return trackpositions.at(track).at(1);
}
// ----------------------------------------------------------------------------------------------------------------------------------
// getTrackEndPos ENDE


//
// Nexttracknumber
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_dat::Nexttracknumber()
{
    if (tracknumber+1 < trackpositions.size())
    {
        tracknumber++;
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------
// Nexttracknumber ENDE


//
// Lasttracknumber
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_dat::Lasttracknumber()
{
    if (tracknumber-1 >=0)
    {
        tracknumber--;
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------
// Lasttracknumber ENDE


//
// isnext
// ----------------------------------------------------------------------------------------------------------------------------------
//
bool C_dat::isnext()
{
    bool end= false;                    // Abbruchbedingung fuer Schleife
    int i = 0;                          // Iterator fuer Abbruch nach number_event_search erfolglosen Anfragen

    int num = eventnumber;

    while(!end)
    {
        i++;
        num++;                                  // Erhoehung der Eventnummer.
        QString e = QString::number(num);       // Umwandeln der Nummer in String

        QString filename = eventdirection + e;  // Pfad fuer Eventdatei zusammenstellen

        QFile testfile;
        testfile.setFileName(filename);         // Datei mit Pfad oeffnen

        if(testfile.exists())                   // Existiert Datei? -> Ja, dann ist dies die naechste Eventnummer
        {
            end = true;                         // Schleife kann abgebrochen werden
            nexteventnumber = num;              // Naechste Eventnummer wird in nexteventnumber gespeichert
            return true;                        // true wird zurueckgegeben
        }

        if (i>number_event_search)              // Abbruchbedingung fuer Schleife pruefen. Wenn Schleife oefter als number_event_search durchlaufen wurden, dann Schleife verlassen
        {
            end = true;                         // Schleife wird abgebrochen
            return false;                       // false wird zurueckgeben
        }
    }
    return false;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// isnext ENDE


bool C_dat::islast()
{
    // gleiches Vorgehen wie bei isnext()
    bool end= false;
    int i = 0;           // Iterator fuer Abbruch nach 100 erfolglosen Anfragen

    int num = eventnumber;

    while(!end)
    {
        i++;
        num--;
        QString e = QString::number(num);

        QString filename = eventdirection + e;

        QFile testfile;
        testfile.setFileName(filename);

        if(testfile.exists())
        {
            end = true;
            previouseventnumber = num;
            return true;
        }

        if ((i>number_event_search)|| (num<=0))
        {
            end = true;
            return false;
        }
    }
    return false;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// islast ENDE


//
// readData
// ----------------------------------------------------------------------------------------------------------------------------------
//
bool C_dat::readData()
{
    if(true)
    {

        // aktuelle Daten leeren. Es wird immer nur ein Event temporaer in C_dat gespeichert
        tracklist.clear();
        trackpositions.clear();
        average.clear();
        average_deviation.clear();
        tracknumber = 0;

        active_fibers = 0;
        trigger_value = 0;
        maximum_value = 0;



        // Datei oeffnen. Dateiname ist Nummer, welche in aktueller eventnumber gespeichert ist
        QString e = QString::number(eventnumber);
        QString filename = eventdirection + e;
        m_file->setFileName(filename);


        // Ausgabe, wenn Datei nicht existiert
        if(m_file->exists())
        {}
        else
        {
            qDebug()<< filename << " not existing";
            return false;
        }
        // oefnnen der Datei
        m_file->open(QIODevice::ReadOnly);


        // xz und yz Arrays auslesen
        //

        //xz Array
        m_file->seek(29);                       // zur Position in der Datei gehen, ab der Daten fuer xz Array beginnen

        double arr[30][15];                     // Array fuer Auslese. Wird dann gleich in xzArray uebertragen.

        for (int i=0; i < 15; i++)
        {
            for (int j=0; j<30; j++)
            {
                m_file->read((char*) &arr[j][i], sizeof(arr[j][i]));    // Einlesen der einzelnen Werte in arr
                xzArray[j][i] = ((float) arr[j][i]);                    // Uebertragen der Werte von arr in xzArray

                // Anzahl aktiver Fiber errechnen
                if (xzArray[j][i] != 0)
                {
                    active_fibers++;
                }

                //Maximale Energiedeposition finden
                if (xzArray[j][i] > maximum_value)
                {
                    maximum_value = xzArray[j][i];
                }

            }
        }




        //yz Array
        // gleiches Vorgehen wie bei xz Array
        m_file->seek(3629);

        double arry[30][15];

        for (int i=0; i < 15; i++)
        {
            for (int j=0; j<30; j++)
            {
                m_file->read((char*) &arry[j][i], sizeof(arry[j][i]));
                yzArray[j][i] = ((float) arry[j][i]);

                // Anzahl aktiver Fiber errechnen
                if (yzArray[j][i] != 0)
                {
                    active_fibers++;
                }

                //Maximale Energiedeposition finden
                if (yzArray[j][i] > maximum_value)
                {
                    maximum_value = yzArray[j][i];
                }
            }
        }


\
        //
        // hit to Track assignment auslesen + zuordnen
        //
        // Hierfuer werden zwei weitere Arrays [30][15] ausgelesen, in denen die einzelnen Kanaele den
        // zugehoerigen Tracks zugeordnet werden. Beispiel: xz_hit_to_track[1][3] = 1 -> Kanal x=1, z=3 gehoert zu Track 1.
        // Die Zuordnung wird benoetigt um die Energiewerte entlang eines Tracks auszugeben.

        //xz auslesen
        //m_file->seek(14153);
        m_file->seek(187721);

        int xz_hit_to_track [30][15];

        for (int i=0; i < 15; i++)
        {
            for (int j=0; j<30; j++)
            {
                m_file->read((char*) &xz_hit_to_track[j][i], sizeof(xz_hit_to_track[j][i]));
            }
        }



        //yz auslesen
        //m_file->seek(15953);
        m_file->seek(189521);

        int yz_hit_to_track [30][15];

        for (int i=0; i < 15; i++)
        {
            for (int j=0; j<30; j++)
            {
                m_file->read((char*) &yz_hit_to_track[j][i], sizeof(yz_hit_to_track[j][i]));
            }
        }




        //
        // Zuordnung von Tracks aus der Datei
        //
        //

        //Anzahl an Tracks auslesen
        unsigned int number_of_tracks = 0;  // Hilfsvariable fuer Auslese
        unsigned int nu = 0;                // Hilfsvariable fuer Auslese
        unsigned int num = 0;

        m_file->seek(187709);
        m_file->read((char*) &nu, sizeof(nu));
        m_file->read((char*) &num, sizeof(num));
        m_file->read((char*) &number_of_tracks, sizeof(number_of_tracks));

        // Wenn im Event Tracks gefunden wurden, dann tracknumber auf 0 setzen
        if (number_of_tracks > 0)
        {
            tracknumber = 0;
        }


        // Alle Tracks, die im Event existieren werden durchlaufen (n als Iterator)
        for (int n=1; n <= number_of_tracks; n++)
        {
            // Liste aus Energiewerten entlang des Tracks erstellen
            QList<float> track;

            // Track to Hit Assignemt durchfuehren.
            // Iterieren ueber die Arrays
            for (int i=0; i < 15; i++)
            {
                for (int j=0; j<30; j++)
                {
                    if(xz_hit_to_track[j][i] == n)                  // Wenn die aktuelle Tracknummer n in xz_hit_to_track gefunden wird, dann
                    {                                               // wird der Energiewert des entsprechenden Kanals aufgenommen. Gleiches Prinzip
                        track.append(xzArray[j][i]);                // wird fuer xy_hit_to_track angewandt
                    }

                    if(yz_hit_to_track[j][i] == n)
                    {
                        track.append(yzArray[j][i]);
                    }

                }


            }

            tracklist.append(track);                                // Die Energiewerte entlang des Tracks werden in der tracklist-Liste angefuegt.



            // Berechnung des Mittelwert und der Abweichung der deponierten Energie

            for (int y =0; y < tracklist.length(); y++)
            {
                float m = 0;

                for (int i = 0; i < tracklist.at(y).length(); i++)\
                {
                    m = m+ tracklist.at(y).at(i);
                }

                average.append(m/tracklist.at(y).length());

                m = 0;

                for (int i = 0; i < tracklist.at(y).length(); i++)\
                {
                    m = m+ (tracklist.at(y).at(i)- average.at(y))*(tracklist.at(y).at(i)- average.at(y));
                }

                average_deviation.append(sqrt(m/tracklist.at(y).length()));

            }





            //
            // 3D Positionen auslesen und speichern
            //


            //m_file->seek(17753+(n-1)*104 +6*8);
            m_file->seek(191321+(n-1)*56 );
            // Positionen
            double xa = 0;
            double ya = 0;
            double za = 0;
            double xe = 0;
            double ye = 0;
            double ze = 0;

            m_file->read((char*) &xa, sizeof(xa));
            m_file->read((char*) &ya, sizeof(ya));
            m_file->read((char*) &za, sizeof(za));
            m_file->read((char*) &xe, sizeof(xe));
            m_file->read((char*) &ye, sizeof(ye));
            m_file->read((char*) &ze, sizeof(ze));



            // Koordinatensystem umwandeln

            // Normierung

            xa = xa/30;
            ya = ya/30;
            za = za/30 ;
            xe = xe/30;
            ye = ye/30;
            ze = ze/30 ;

            // Anpassen auf OpenGL Koordinatensystem
            // -> um Faktor 2 vergroesern und um -1 in alle Richtungen verschieben

            xa = xa*2 -1;
            ya = ya*2 -1;
            za = za*2 +1;
            xe = xe*2 -1;
            ye = ye*2 -1;
            ze = ze*2 +1;


            // Anfangs- und Endpositionen als Vektoren erstellen
            QVector3D Anfang(xa,za,ya);
            QVector3D Ende(xe,ze,ye);

            QList <QVector3D> addAnfangEnde;

            addAnfangEnde.append(Anfang);
            addAnfangEnde.append(Ende);

            trackpositions.append(addAnfangEnde);           // Anfangs- und Endposition des n-ten Tracks in die trackpositions-Liste aufnehmen



        }

        // File schliesen
        m_file->close();
    }
    return true;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// readData ENDE


//
// addtracktolist
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_dat::addtracktolist(QList<float> tr)
{
    tracklist.append(tr);
}
// ----------------------------------------------------------------------------------------------------------------------------------
// addtracktolist ENDE


//
// getxzArray
// ----------------------------------------------------------------------------------------------------------------------------------
//
float C_dat::getxzArray(int i, int j)
{
    if ((i<30) && (j<15))
    return xzArray[i][j];

    else return -1;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// getxzArray ENDE


//
// getyzArray
// ----------------------------------------------------------------------------------------------------------------------------------
//
float C_dat::getyzArray(int i, int j)
{
    if ((i<30) && (j<15))
    return yzArray[i][j];

    else return -1;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// getyzArray ENDE


//
// getnormfaktor
// ----------------------------------------------------------------------------------------------------------------------------------
//
float C_dat::getnormfaktor()
{
    return m_normfaktor;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// getnormfaktor ENDE



//
// getlength
// ----------------------------------------------------------------------------------------------------------------------------------
//
int C_dat::getlength()
{
    if (tracklist.size() >= 1)
    {
        return tracklist.at(tracknumber).size();
    }
    else
        return 0;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// getlength ENDE



//
// nexttrack
// ----------------------------------------------------------------------------------------------------------------------------------
//
bool C_dat::nexttrack()
{

    if (tracknumber +1 < trackpositions.size())
    {
        tracknumber++;
        return true;
    }
    else
    {
        return false;
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------
// nexttrack ENDE



//
// lasttrack
// ----------------------------------------------------------------------------------------------------------------------------------
//
bool C_dat::lasttrack()
{
    if (tracknumber -1 >= 0)
    {
        tracknumber--;
        return true;
    }
    else
    {
        return false;
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------
// lasttrack ENDE



//
// getData
// ----------------------------------------------------------------------------------------------------------------------------------
//
float C_dat::getData(int i)
{
    return tracklist.at(tracknumber).at(i);
}
// ----------------------------------------------------------------------------------------------------------------------------------
// getData ENDE



//
// last
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_dat::last()
{
    eventnumber = previouseventnumber;
    readData();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// last ENDE



//
// next
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_dat::next()
{
    eventnumber= nexteventnumber;
    readData();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// next ENDE



//
// live
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_dat::live()
{
    // Vorgehen wie bei isnext()

    bool end= false;
    int i = 0;           // Iterator fuer Abbruch nach number_event_search erfolglosen Anfragen

    int num = eventnumber;
    int newest_number = eventnumber;        // Zwischenspeicherung der neuesten Eventnummer

    while(!end)
    {
        i++;
        num++;
        QString e = QString::number(num);

        QString filename = eventdirection + e;

        QFile testfile;
        testfile.setFileName(filename);

        if(testfile.exists())
        {
            newest_number = num;            // wie bei isnext()
            i = 0;                          // wenn neuestes Event gefunden, dann wird der Iterator wieder auf 0 gesetzt
        }                                   // und es wird weiter gesucht, bis die Abbruchbedingung erfuellt wird

        if (i>number_event_search)          // Abbruchbedingung
        {
            end = true;
        }
    }
    eventnumber = newest_number;

    readData();
}
// ----------------------------------------------------------------------------------------------------------------------------------
// live ENDE



//
// islasttrack
// ----------------------------------------------------------------------------------------------------------------------------------
//
bool C_dat::islasttrack()
{
    if (tracknumber -1 >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------
// islasttrack ENDE



//
// isnexttrack
// ----------------------------------------------------------------------------------------------------------------------------------
//
bool C_dat::isnexttrack()
{
    if (tracknumber +1 < trackpositions.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------
// isnexttrack ENDE



//
// get_number_event_search
// ----------------------------------------------------------------------------------------------------------------------------------
//
int C_dat::get_number_event_search()
{
    return number_event_search;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// get_number_event_search ENDE


//
// set_number_event_search
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_dat::set_number_event_search(int e)
{
    number_event_search = e;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// set_number_event_search ENDE



//
// setnormfaktor
// ----------------------------------------------------------------------------------------------------------------------------------
//
void C_dat::setnormfaktor(float n)
{
    m_normfaktor = n;
}
// ----------------------------------------------------------------------------------------------------------------------------------
// setnormfaktor ENDE



//
// get_average
// ----------------------------------------------------------------------------------------------------------------------------------
//
float C_dat::get_average()
{
    return average.at(tracknumber);
}
// ----------------------------------------------------------------------------------------------------------------------------------
// get_average ENDE



//
// get_average_deviation
// ----------------------------------------------------------------------------------------------------------------------------------
//
float C_dat::get_average_deviation()
{
    return average_deviation.at(tracknumber);
}
// ----------------------------------------------------------------------------------------------------------------------------------
// get_average_deviation ENDE

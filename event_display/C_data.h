#ifndef C_DATEN_H
#define C_DATEN_H


#include <QDebug>
#include <QObject>
#include <QGLWidget>
#include <QtGui>
#include <QFile>
#include <cmath>

#include <TVector3.h>





class C_dat : QObject
{

public:
    C_dat ();                                   // Konstruktor. Belegung der Variablen mit Anfangswerten


    bool isnext();                              // Abfrage, ob es ein naechstes Event gibt
    bool islast();                              // Abfrage, ob es ein vorheriges Event gibt

    bool readData();                            // Liest Event aus Eventdatei ein

    float getxzArray (int i, int j);            // Gibt [i][j] von xzArray zurueck
    float getyzArray (int i, int j);            // Gibt [i][j] von xzArray zurueck

    float getnormfaktor();
    void setnormfaktor (float n);

    int getTrackSize();

    int gettracknumber();

    void Lasttracknumber();
    void Nexttracknumber();

    QVector3D getTrackStartPos (int track);
    QVector3D getTrackEndPos (int track);


    int getlength();                            // Anzahl der Energiewerte des ausgewaehlten Tracks (identifiziert ueber tracknumber)

    bool nexttrack();                           // Gibt es einen naechsten Track?
    bool lasttrack();                           // Gibt es einen letzten Track?

    float getData (int i);                      // Gibt i-ten Energiewert des ausgewaehlten Tracks zurueck

    void next();
    void last();
    void live();

    bool isnexttrack();
    bool islasttrack();

    int getEventnumber ();

    int get_number_event_search();
    void set_number_event_search(int e);

    float get_average();
    float get_average_deviation();

    void open_number(int number);               // Geht zum Event der uebergegebenen Nummer

    int get_active_fibers ();                   // Rueckgabe von active_fibers
    int get_trigger_value ();                   // Rueckgabe von trigger_value
    int get_maximum_value ();                   // Rueckgabe von maximum_value

    void addtracktolist (QList<float> tr);



private:

    QFile* m_file;                              // Datei in der Event eingelesen wird

    float m_normfaktor;                         // Normfaktor: Obere Grenze der statischen Achsen (Energie in MIP-energien)

    float xzArray [30][15];                     // xz Array enthaelt die Detektorwerte der xz Seite
    float yzArray [30][15];                     // xz Array enthaelt die Detektorwerte der xz Seitek

    int number_event_search;                    // Anzahl an Eventnummern, die bei der Suche nach einem neuen Event durchlaufen werden (Abbruchbedingung fuer Suche)

    QList <QList <QVector3D> > trackpositions;  // Liste ueber alle Tracks mit Liste der Anfangs- und Endposition der Tracks

    QList <QList <float> > tracklist;           // Liste ueber alle Tracks mit Liste der Energiewerte entlang eines Tracks

    int tracknumber;                            // Nummer des gerade ausgewaehlten Tracks. Alle Tracks eines Events sind fortlaufend nummeriert. Entsprechend der Nummer sich alle Daten in den Listen gespeichert.

    int eventnumber;                            // Nummer des aktuellen Events





    QString eventdirection;                     // Pfad zu Eventdateien

    int nexteventnumber;                        // Nummer des naechsten Events
    int previouseventnumber;                    // Numemr des vorherigen Events

    QList <float> average;                      // Mittelwert der Energiewerte eines Tracks. Jeder Listeneintrag ist ein dem Track mit der entsprechenden Nummer zugeordnet
    QList <float> average_deviation;            // Abweichung des Mittelwert der Energiewerte eines Tracks. Jeder Listeneintrag ist ein dem Track mit der entsprechenden Nummer zugeordnet

    int active_fibers;                          // Anzahl aller aktiven Kanaele
    int trigger_value;                          // Trigger Werte
    int maximum_value;                          // Maximaler Wert in einem Event



protected:


};

#endif // C_DATEN_H

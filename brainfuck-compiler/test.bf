# einlesen bis ENTER (= 10)
[
    >          nächste Zelle für nächstes Zeichen
    ,          einlesen
    ---------- minus 10 damit in Zelle 0 steht wenn es ENTER ist
]

# bei Eingabe 123 entsteht 00 39 40 41 00
                                        ^

# umwandeln der Eingabe in Zahl
<[<] gehe zu Zelle 0 welche leer ist

# bei Eingabe 123 entsteht 00 39 40 41 00
                            ^

[
    # mal 10
    << ++++++++++ overflow pointer auf 254 dann plus 10
    [
        >

    ]
    -------------------------------------- minus 38
    
]
Svar p� sp�rsm�l
================

1)
--
� ha medlemmer som er `protected` kan potensielt for�rsake uventede/u�nskede situasjoner, hvis man
har metoder som tar imot et objekt av egen type, f.eks. en `dot`som tar imot en annen `dot` kan endre dennes beskyttede medlemmer. En annen ulempe er at det kan f�re til latskap, f.eks. `has_color` hadde hatt nytte av en metode; `makeDarker()`, men fordi man har tilgang til medlemmene direkte dropper man � lage metoden. Fordelen er at det ofte sparer deg fra � lage en del kode, spesielt gettere og settere.

2)
--
Ved � fjerne avhengigheten av fltk i animation_canvas ville kun implementasjonen m�tte endres, dvs. 
de klassene som er spesifikt til fyrverkeri og ikke de som kun sier noe om animering.
Man b�r vel ogs� ikke ta utgangspunkt i at biblioteket automagisk vet hvilket vindu/ramme man �nsker � tegne i, slik som fltk gj�r, uten at jeg ser hvordan jeg skulle gjort dette akkurat n�.


3)
--
Ville sannsynligvis brukt et eget namespace til `animated`, `animation_canvas`, `has_color` og `is_vector`  kalt f.eks. `my_animation` el.l. slik at de ikke forurenset navnerommet til implementerende klasser.
Kunne ogs� hatt et eget navnerom til `dot`, `rocket` og `fireworks`, men anser det som mindre viktig.
De tre foreg�ende klassene er de som m�tte ha brukt `using namespace my_animation`.

4)
--
`animation_canvas` kunne fint ha v�rt implementert med templates, fordelen hadde v�rt at man kunne presisert
at man kunne sjekke at det som legges til arver flere enn �n klasse. En fordel er ogs� at det reduserer 
overhead en smule, ved at det genereres �n metode per type som implementerer metodene, ulempen her er dog
at det vil gj�re den eksekverbare filen st�rre. Templates kan ogs� gj�re koden mer kompleks og "kanskje" 
vanskeligere � sette seg inn i.

5)
--
Klassen *rocket* er definert med en vektor av *dot* som gj�r at alt en rakett kan inneholde er dotter, ikke
f.eks. stjerner (med mindre de arver *dot*) eller andre typer raketter. Den burde ha en vektor med *animated&#1645;* og evt. forsikret seg om at det som legges til raketten ogs� arver *is_vector*, el.l. 

*dot* burde ogs� ha en *copy-constructor* slik at dens *has_color* attributter blir riktige n�r den kopieres, red, green og blue char pekerne kan da settes i konstrukt�ren til *has_color* og fortsatt bli riktige om *dot* kopieres.

Skulle ogs� gjerne likt � hatt en del ekstra metoder for � endre/sjekke egenskaper ved de ulike klassene, det hadde 
f.eks v�rt fordelaktig � kunne sette fargene p� en `dot` via en `rocket`, slik at man da lettere kan kontrollere fargetyngde, etc.


PS:
Glemte at det var en tredje oppgave helt til i dag, s� `custom` b�rer beklageligvis preg av hastverksarbeid. 
Alt i alt en spennende oppgave.
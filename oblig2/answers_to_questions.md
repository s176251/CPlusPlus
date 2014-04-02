Svar på spørsmål
================

1)
--
Å ha medlemmer som er `protected` kan potensielt forårsake uventede/uønskede situasjoner, hvis man
har metoder som tar imot et objekt av egen type, f.eks. en `dot`som tar imot en annen `dot` kan endre dennes beskyttede medlemmer. En annen ulempe er at det kan føre til latskap, f.eks. `has_color` hadde hatt nytte av en metode; `makeDarker()`, men fordi man har tilgang til medlemmene direkte dropper man å lage metoden. Fordelen er at det ofte sparer deg fra å lage en del kode, spesielt gettere og settere.

2)
--
Ved å fjerne avhengigheten av fltk i animation_canvas ville kun implementasjonen måtte endres, dvs. 
de klassene som er spesifikt til fyrverkeri og ikke de som kun sier noe om animering.
Man bør vel også ikke ta utgangspunkt i at biblioteket automagisk vet hvilket vindu/ramme man ønsker å tegne i, slik som fltk gjør, uten at jeg ser hvordan jeg skulle gjort dette akkurat nå.


3)
--
Ville sannsynligvis brukt et eget namespace til `animated`, `animation_canvas`, `has_color` og `is_vector`  kalt f.eks. `my_animation` el.l. slik at de ikke forurenset navnerommet til implementerende klasser.
Kunne også hatt et eget navnerom til `dot`, `rocket` og `fireworks`, men anser det som mindre viktig.
De tre foregående klassene er de som måtte ha brukt `using namespace my_animation`.

4)
--
`animation_canvas` kunne fint ha vært implementert med templates, fordelen hadde vært at man kunne presisert
at man kunne sjekke at det som legges til arver flere enn èn klasse. En fordel er også at det reduserer 
overhead en smule, ved at det genereres èn metode per type som implementerer metodene, ulempen her er dog
at det vil gjøre den eksekverbare filen større. Templates kan også gjøre koden mer kompleks og "kanskje" 
vanskeligere å sette seg inn i.

5)
--
Klassen *rocket* er definert med en vektor av *dot* som gjør at alt en rakett kan inneholde er dotter, ikke
f.eks. stjerner (med mindre de arver *dot*) eller andre typer raketter. Den burde ha en vektor med *animated&#1645;* og evt. forsikret seg om at det som legges til raketten også arver *is_vector*, el.l. 

*dot* burde også ha en *copy-constructor* slik at dens *has_color* attributter blir riktige når den kopieres, red, green og blue char pekerne kan da settes i konstruktøren til *has_color* og fortsatt bli riktige om *dot* kopieres.

Skulle også gjerne likt å hatt en del ekstra metoder for å endre/sjekke egenskaper ved de ulike klassene, det hadde 
f.eks vært fordelaktig å kunne sette fargene på en `dot` via en `rocket`, slik at man da lettere kan kontrollere fargetyngde, etc.


PS:
Glemte at det var en tredje oppgave helt til i dag, så `custom` bærer beklageligvis preg av hastverksarbeid. 
Alt i alt en spennende oppgave.
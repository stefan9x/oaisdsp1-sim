# Uputstvo za instalaciju CCS i podešavanje simulatora

## Instalacija
1. Skinuti [CCS](https://drive.google.com/file/d/1rL_pEQjOGyCzGNipdwE42jQkOQdXKiu8/view?usp=sharing) i raspakovati
2. Pokrenuti **ccs_setup_6.1.3.00034.exe**
3. Pod **Processor Support** proširiti **Single Core DSPs** i izabrati **C55x Device Support** i **TI C55x Compiler**. (Možete izabrati sve ako niste sigurni, ali nema potrebe)
4. Ostalo sve default.
5. Nakon instalacije kopirati foldere **common** i **simulation** iz foldera **CCS6 patch** u folder **ccs_base** koji se nalazi tamo gdje ste instalirali CCS (default putanja C:\ti\ccsv6\)

  **NAPOMENA: nemojte koristiti simulator template koji dodje u CCS.rar fajlu**
	
## Pokretanje simulatora
1. Skinuti repozitorijum klikom na **Clone or download** -> **Download ZIP**
2. Raspakovati zip
3. Pokrenuti CCS i izabrati workspace folder
4. Importovati gotovu vježbu ili prazan simulator_template_fixed(ako želite da sami kucate)

  **NAPOMENA: Uvijek čekirajte *"Copy projects into workspace"* da bi vam kopirao projekat u vaš workspace**

mode (-1)

disp("")
disp("Tests de non-r�gression pour Scilab-3.0 : d�but");
disp("")

lines(0);

// dans la variable num_test mettre tous les num�ros de bugs corrig�s dans la version 3.0

num_test = [1014,1004,1003,979,946,945,943,942,925,924,862,859,857,853,800,793,790,750,699,682,681,656,654,650,649,632,629,625,623,612,610,608,604,584,575,570,569,568,566,564,558,557,553,549,546,545,542,534,528,525,502,498,488,487,480,477,476,475,474,470,467,464,461,71,55]

// 683,973

for k = num_test
   exec('bug' + string(k) + '.sci')
end

disp("") 
disp("Tests de non-r�gression pour Scilab-3.0 : fin");
disp("")

quit;
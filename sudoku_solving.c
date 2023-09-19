//w1,w2,w3... un ensemble de solution 
//fonction economique c(w) 
//fonction de voisinage V : OMEGA donne 2 puissance OMEGA 

//à chaque itération une solution omega prime est choisit arbitrairement parmi toutes les solutions possibles 

//graphe de sudoku > les sommets sont les casses de la grille, deux sommets osnt liés s'ils sont sur la même ligne, colonne, sous carré 


void solve(){
    //INITIALISATION 

    double delta = 0.1;
    double ep = 1920/2;
    double Temperature = 1920/2;

    //choisir omega arbitrairement 
    //omega = choisirSolution();

    while(T >= 0.00273852){
        for(int k = 1; k <= 81; k++){
            //choisir i et j dans {1,9}
            t = omega;
            c1 = c;
            do{

            }
            while (w == t)
            
            t = //omega ij

            c2 = cout(omega)
            c_prime = c-c1+c2

            //choisir u dans   [0,1]


            if(u <= e*((c_prime-c)/T)){
                c = c_prime;//acceptation
            } else {
                omega = t;//rejet
            }
            if(c == 0){
                //écrire omega dans la case 
            }
        }
        T = ( T / ( 1 + ( log(1 + delta) / exp( p + 1 )) * T ));
        
    }
}
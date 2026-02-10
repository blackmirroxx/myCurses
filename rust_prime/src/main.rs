use std::io;

// trouve le plus petit nombre premier strictement supérieur à `b`.
fn least_prime_greater_than(b: i32) -> Option<i32> {
    let primes = vec![2, 3, 5, 7, 11, 13, 19, 23, 29];
    primes.into_iter().find(|&v| v > b)
}

fn main() {
    // Test de division flottante
    let test = 1.0 / 4.0; 
    println!("{}", test);

    println!("least prime greater than:"); 

    // Lire l'entrée utilisateur 
    let mut input = String::new(); 
    io::stdin()
        .read_line(&mut input)
        .expect("Échec de la lecture de l'entrée"); 

    // Convertir en entier 
    let p: i32 = match input.trim().parse() {
        Ok(num) => num, 
        Err(_) => {
            eprint!("Erreur : veuillez entrer un nombre valide. ");
            return;
        }
    };

    // Aicher le résultat 
    match least_prime_greater_than(p) {
        Some(prime) => println!("is {}", prime),
        None => println!("Aucun nombre premier plus grand que {} dans la liste.", p),
    }
}

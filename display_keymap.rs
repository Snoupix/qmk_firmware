use std::fs::File;
use std::io::{self, Read};

static PATH: &str = "./keyboards/crkbd/keymaps/snoupix/keymap.c";

fn main() -> io::Result<()> {
    let mut file = File::open(PATH)?;
    let mut content = String::new();
    file.read_to_string(&mut content)?;

    let mut keymap = content
        .lines()
        .skip_while(|l| !l.contains("keymaps"))
        .take_while(|l| !l.contains("};"));

    println!("{}", keymap.collect::<String>());

    Ok(())
}

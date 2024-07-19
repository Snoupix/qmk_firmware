use std::fs::File;
use std::io::{self, Read};

static PATH: &str = "./keyboards/crkbd/keymaps/snoupix/keymap.c";

fn main() -> io::Result<()> {
    let mut file = File::open(PATH)?;
    let mut content = String::new();
    file.read_to_string(&mut content)?;

    let keymaps_lines = content
        .lines()
        .skip_while(|l| !l.contains("keymaps"))
        .take_while(|l| !l.contains("};"))
        .skip(1)
        .collect::<Vec<_>>();

    let mut keymaps = Vec::with_capacity(
        keymaps_lines
            .iter()
            .fold(0, |len, line| len + line.contains(");") as usize),
    );

    for i in 0..keymaps.capacity() {
        keymaps.push(
            keymaps_lines
                .iter()
                .take_while(|l| !l.contains("),"))
                .collect::<Vec<_>>(),
        );
    }

    for l in keymaps.first().unwrap() {
        println!("{}", l);
    }

    Ok(())
}

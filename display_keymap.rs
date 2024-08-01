use std::collections::HashMap;
use std::env;
use std::fs::File;
use std::io::{self, Read};

static PATH: &str = "./keyboards/crkbd/keymaps/snoupix/keymap.c";

fn main() -> io::Result<()> {
    let args = env::args();
    if args.len() != 2 {
        eprintln!("Give a layer name to display its keymap");
        std::process::exit(1);
    }

    let layer_name = args.into_iter().nth(1).unwrap().to_lowercase();
    let mut file = File::open(PATH)?;
    let mut content = String::new();
    file.read_to_string(&mut content)?;
    let lines = content.lines();

    let layers = lines
        .clone()
        .skip_while(|l| !l.contains("enum layers"))
        .take_while(|l| !l.contains("};"))
        .skip(1)
        .map(|l| l.trim().replace([' ', ','], "").to_lowercase())
        .collect::<Vec<_>>();

    let keymaps_lines = lines
        .skip_while(|l| !l.contains("keymaps"))
        .take_while(|l| !l.contains("};"))
        .skip(1)
        .collect::<Vec<_>>();

    let mut keymaps = HashMap::with_capacity(
        keymaps_lines
            .iter()
            .fold(0, |len, line| len + line.contains(" ),") as usize),
    );

    assert_eq!(keymaps.capacity(), layers.len());

    let mut keymaps_lines = keymaps_lines.into_iter();

    // TODO: fix this, either update the iterator or take chunks of it since keymaps have the same
    // line count ?
    for i in 0..keymaps.capacity() {
        keymaps.insert(
            &layers[i],
            keymaps_lines
                .take_while(|l| !l.contains("),"))
                .collect::<Vec<_>>(),
        );
    }

    eprintln!("Layer {} not found on layers {:?}", layer_name, layers);
    let index = layers.iter().position(|name| name.contains(&layer_name));
    if index.is_none() {
        eprintln!("Layer {} not found on layers {:?}", layer_name, layers);
        std::process::exit(1);
    }
    let index = index.unwrap();

    for l in keymaps.get(&layers[index]).unwrap() {
        println!("{}", l);
    }

    Ok(())
}

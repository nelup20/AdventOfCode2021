use std::fs;

fn main() {
    let data: String = fs::read_to_string("input.txt").expect("Error reading file");
    let input: Vec<Vec<&str>> = data.lines()
                                    .collect::<Vec<&str>>()
                                    .iter()
                                    .map(|line| line.split("").collect())
                                    .collect();

    let mut stack: Vec<&str> = Vec::new();

    let mut result = 0;

    for line in input {
        for char in line {
            match char {
                "[" | "(" | "{" | "<" => stack.push(char),
                "]" => if stack.pop().unwrap() != "[" { result += 57; break; },
                ")" => if stack.pop().unwrap() != "(" { result += 3; break; },
                "}" => if stack.pop().unwrap() != "{" { result += 1197; break; },
                ">" => if stack.pop().unwrap() != "<" { result += 25137; break; },
                _ => {}
            }
        }
    }

    println!("Result: {}", result);
}

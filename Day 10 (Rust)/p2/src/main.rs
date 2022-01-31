use std::fs;

fn main() {
    let data: String = fs::read_to_string("input.txt").expect("Error reading file");
    let input: Vec<Vec<&str>> = data.lines()
                                    .collect::<Vec<&str>>()
                                    .iter()
                                    .map(|line| line.split("").collect())
                                    .collect();

    let mut scores: Vec<i64> = Vec::new();

    for line in input {
        if !is_corrupted(&line) {
            let mut stack: Vec<&str> = Vec::new();
            let mut score = 0;

            for char in line {
                match char {
                    "[" | "(" | "{" | "<" => stack.push(char),
                    "]" | ")" | "}" | ">" => { stack.pop(); },
                    _ => {}
                }
            }

            stack.reverse();

            for char in stack {
                match char {
                    "(" => score = (score * 5) + 1,
                    "[" => score = (score * 5) + 2,
                    "{" => score = (score * 5) + 3,
                    "<" => score = (score * 5) + 4,
                    _ => {}
                }
            }

            scores.push(score);
        }
    }

    scores.sort();

    let result = scores[scores.len() / 2];
    println!("Result: {}", result);
}

fn is_corrupted(line: &Vec<&str>) -> bool {
    let mut stack: Vec<&str> = Vec::new();

    for &char in line {
        match char {
            "[" | "(" | "{" | "<" => stack.push(char),
            "]" => if stack.pop().unwrap() != "[" { return true; },
            ")" => if stack.pop().unwrap() != "(" { return true; },
            "}" => if stack.pop().unwrap() != "{" { return true; },
            ">" => if stack.pop().unwrap() != "<" { return true; },
            _ => {}
        }
    }

    return false;
}
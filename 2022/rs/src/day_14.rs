use std::collections::HashMap;

const CHALLENGE_INPUT: &str = include_str!("../14.input");
const EXAMPLE_INPUT: &str = "498,4 -> 498,6 -> 496,6\n503,4 -> 502,4 -> 502,9 -> 494,9"; 

enum Tile {
    Foreground,
    Background,
    Sand,
}

struct Map {
    min_x: i32,
    max_x: i32,
    min_y: i32,
    max_y: i32,
    tiles: HashMap<(i32, i32), Tile>,
}

pub fn part_1() -> &'static str {
    return EXAMPLE_INPUT;
}

#[cfg(test)]
mod test {
    use crate::day_14;

    #[test]
    fn part1_test() {
        assert_eq!(day_14::part_1(), day_14::EXAMPLE_INPUT);
    }
}

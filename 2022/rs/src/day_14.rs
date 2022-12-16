use std::collections::HashMap;
use std::cmp;

pub const CHALLENGE_INPUT: &str = include_str!("../14.input");
pub const EXAMPLE_INPUT: &str = "498,4 -> 498,6 -> 496,6\n503,4 -> 502,4 -> 502,9 -> 494,9"; 

const SAND_SOURCE: (i32, i32) = (500, 0);

#[derive(Debug, PartialEq)]
enum Tile {
    Foreground,
    Background,
    Sand,
}

fn parse_input(input: &str) -> HashMap<(i32, i32), Tile> {
    let mut tiles: HashMap<(i32, i32), Tile> = HashMap::new();

    let mut background_segments: Vec<Vec<(i32, i32)>> = Vec::new();
    let foreground_lines = input.split('\n');
    for line in foreground_lines {
        // extract segments from the lines
        let line_segments = line.split(" -> ");
        background_segments.push(Vec::new());

        for segment in line_segments {
            // now we have 1,13 -> 2,14 we need to make this part of "map"
            let coordinate = segment.split(',');
            let coordinate = coordinate.collect::<Vec<&str>>();
            let coordinate: (i32, i32) = (coordinate[0].parse().unwrap(), coordinate[1].parse().unwrap());
            
            if let Some(segments) = background_segments.last_mut() {
                segments.push(coordinate);
            }
        }
    }

    for segment in background_segments {
        for section in segment.windows(2) {
            let sx = cmp::min(section[0].0, section[1].0);
            let sy = cmp::min(section[0].1, section[1].1);
            let bx = cmp::max(section[0].0, section[1].0);
            let by = cmp::max(section[0].1, section[1].1);
            for x in sx..=bx {
                for y in sy..=by {
                    tiles.insert((x, y),Tile::Background);
                }
            }
        }
    }

    return tiles;
}

fn sand_falling(solid_floor: bool, sand_position: (i32, i32), map: &mut HashMap<(i32, i32), Tile>, dropoff: i32) -> bool {
    if sand_position.1 == dropoff {
        return true;
    }

    if map.contains_key(&sand_position) {
        return false;
    }

    for x in [sand_position.0, sand_position.0 - 1, sand_position.0 + 1] {
        if sand_falling(solid_floor, (x, sand_position.1 + 1), map, dropoff) && !solid_floor {
            return true;
        }
    }
    map.insert(sand_position, Tile::Sand);

    return false;
}

// Goes until a piece of sand falls off of the map
fn simulate_sand(solid_floor: bool, origin: (i32, i32), map: &mut HashMap<(i32, i32), Tile>) -> i32 {
    // find bottom point of map
    let mut low_y: i32 = 0;
    for (point, value) in map.into_iter() {
        if point.1 > low_y {
            low_y = point.1;
        }
    }

    sand_falling(solid_floor, origin, map, low_y + 2);

    let mut counter = 0;
    for (point, value) in map.into_iter() {
        if *value == Tile::Sand {
            counter += 1;
        }
    }
    return counter;
}

pub fn part_1(input: &str) -> i32 {
    let mut map = parse_input(input);
    return simulate_sand(false, SAND_SOURCE, &mut map);
}
pub fn part_2(input: &str) -> i32 {
    let mut map = parse_input(input);
    return simulate_sand(true, SAND_SOURCE, &mut map);
}

#[cfg(test)]
mod test {
    use crate::day_14;

    #[test]
    fn part1_test() {
        assert_eq!(day_14::part_1(day_14::EXAMPLE_INPUT), 24);
        assert_eq!(day_14::part_1(day_14::CHALLENGE_INPUT), 757);
    }

    #[test]
    fn part2_test() {
        assert_eq!(day_14::part_2(day_14::EXAMPLE_INPUT), 93);
        assert_eq!(day_14::part_2(day_14::CHALLENGE_INPUT), 24943);
    }
}

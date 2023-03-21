#[no_mangle]
pub extern fn CallMeMaybe(x: u32) -> u32 {
    return (x * 100) + 68;
}

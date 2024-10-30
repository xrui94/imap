// globals.rs  

use crate::c_dll;   // Rust中，main.rs和lib.rs是不同的crate，通常在“Cargo.toml”中配置lib，然后，lib.rs模块会自动被包含到main.rs所在的crate中

use std::sync::Mutex;  
  
// 声明一个可能未初始化的全局变量，使用 Option 和 Mutex  
pub static GLOBAL_DLLAPI: Mutex<Option<c_dll::Api>> = Mutex::new(None);

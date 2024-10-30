mod c_dll;
use c_dll::Api;

mod globals;
use globals::GLOBAL_DLLAPI;

pub fn create_server() {
    // 在 main 函数中初始化 GLOBAL_DLLAPI  
    let mut api_option = GLOBAL_DLLAPI.lock().unwrap();  
    *api_option = Some(Api::new("C:/Users/xrui94/Desktop/projx_xrui94_imap/src-cpp/build/Release/imap.dll").unwrap_or_else(|e| {  
        panic!("Failed to initialize DLL: {}", e);  
    }));  
}

pub fn start_static_server() {
    // 现在 GLOBAL_DLLAPI 已经被初始化了，可以安全地使用它  
    if let Some(api) = GLOBAL_DLLAPI.lock().unwrap().as_ref() {  
        // 使用 api...  
        let _ = api.start_server(1027);
    }  
}

// Learn more about Tauri commands at https://tauri.app/develop/calling-rust/
#[tauri::command]
fn greet(name: &str) -> String {
    // GLOBAL_DLLAPI.say_hello();

    // 现在 GLOBAL_DLLAPI 已经被初始化了，可以安全地使用它  
    if let Some(api) = GLOBAL_DLLAPI.lock().unwrap().as_ref() {  
        // 使用 api...  
        let _ = api.say_hello();
    }

    format!("Hello, {}! You've been greeted from Rust!", name)
}

#[tauri::command]
fn open_file(name: &str) -> String {
    format!("Hello, {}! You've been greeted from Rust!", name)
}

#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    tauri::Builder::default()
        .plugin(tauri_plugin_shell::init())
        .invoke_handler(tauri::generate_handler![
            greet,
            open_file,
        ])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}

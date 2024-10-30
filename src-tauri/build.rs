// #Ref:
// https://github.com/xrui94/3dtiles/blob/master/build.rs
// fn build_win_msvc() {
    
//     //

//     Command::new("cmd")
//         .args(&[
//             "/C",
//             "xcopy",
//             r#".\bin"#,
//             &format!(r#".\target\{}"#, env::var("PROFILE").unwrap()),
//             "/y",
//             "/e",
//         ])
//         .stdout(Stdio::inherit())
//         .output()
//         .unwrap();
// }

fn main() {
    // let dll_path = "./imap.dll";
    // println!("cargo:rustc-env=MY_DLL_PATH={}", dll_path);
    tauri_build::build()
}

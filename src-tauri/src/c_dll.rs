use libloading::{Library, Symbol, Error, library_filename};

type SayHelloFn = unsafe extern fn();
type StartServerFn = unsafe extern fn(i16) -> i8;

pub struct Api {  
    lib: Library,  
}  
  
impl Api {  
    /// Creates a new instance of the Api by loading the specified library.  
    pub fn new(lib_path: &str) -> Result<Self, Error> {  
        // The unsafe block is necessary here because Library::new is unsafe.  
        // We encapsulate the unsafe operation within a safe function by using a Result to handle errors.  
        unsafe {  
            let lib = Library::new(lib_path)?;  
            Ok(Api { lib })  
        }  
    }  
  
    /// Calls the `sayHello` function in the loaded library.  
    pub fn say_hello(&self) -> Result<(), Error> {  
        // We don't need an unsafe block here because we are just calling a safe method on the Symbol.  
        // However, getting the symbol itself is an unsafe operation because it could fail.  
        unsafe {  
            let func: Symbol<SayHelloFn> = self.lib.get(b"sayHello")?;  
            func();  
        }  
        Ok(())  
    }  
  
    /// Starts the server by calling the `startServer` function in the loaded library.  
    pub fn start_server(&self, port: i16) -> Result<i8, Error> {  
        unsafe {  
            let func: Symbol<StartServerFn> = self.lib.get(b"startServer")?;  
            Ok(func(port))  
        }  
    }  
}

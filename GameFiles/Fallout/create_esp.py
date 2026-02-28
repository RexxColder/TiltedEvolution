import struct

def create_fallout_esp(filename, filename_bytes):
    # Fallout 4 ESP file structure
    with open(filename, 'wb') as f:
        # TES4 Header
        f.write(b'TES4')  # File type
        f.write(b'h\x00\x00\x00')  # Header size (0x68 = 104)
        f.write(b'\x00' * 8)  # Header data
        
        # HEDR - Header Data
        f.write(b'HEDR')
        f.write(struct.pack('<I', 12))  # Size
        f.write(struct.pack('<f', 0.9))  # Version
        f.write(struct.pack('<I', 0))    # Unknown
        
        # CNAM - Creator Name
        f.write(b'CNAM')
        f.write(struct.pack('<I', len(filename_bytes)))
        f.write(filename_bytes)
        
        # MAST - Master file (Fallout4.esm)
        f.write(b'MAST')
        f.write(struct.pack('<I', 12))  # Size
        f.write(b'Fallout4.esm')
        f.write(b'\x00')
        
        # DATA - Master data
        f.write(b'DATA')
        f.write(struct.pack('<I', 8))
        f.write(struct.pack('<Q', 0))
        
        # INTV - Interface
        f.write(b'INTV')
        f.write(struct.pack('<I', 4))
        f.write(struct.pack('<I', 1))
        
        # ONAM - Override Names (empty)
        # CNAM - Next Master
        f.write(b'MAST')
        f.write(struct.pack('<I', 15))
        f.write(b'Update.esm\x00')
        
        f.write(b'DATA')
        f.write(struct.pack('<I', 8))
        f.write(struct.pack('<Q', 0))
        
    print(f"Created: {filename}")

# Create basic ESP
create_fallout_esp('FalloutTogether.esp', b'FalloutTogether Mod')

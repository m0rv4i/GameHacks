#include "ammo.h"

bool cheat::Ammo::toggle(const bool enabled) {

    const auto ammoDecrementAddress = baseAddress + AMMO_NOP_OFFSET;
    logger.debug_log(_T("[*] Ammo decrement address at 0x%p"), ammoDecrementAddress);

    const auto grenadeDecrementAddress = baseAddress + GRENADE_NOP_OFFSET;
    logger.debug_log(_T("[*] Grenade decrement address at 0x%p"), grenadeDecrementAddress);

    bool totalSuccess = true;

    if (enabled) {

        pPlayer->PrimaryAmmo = 1337;
        pPlayer->SecondaryAmmo = 1337;
        pPlayer->PrimaryAmmoReserve = 1337;
        pPlayer->SecondaryAmmoReserve = 1337;
        pPlayer->AkimboAmmo = 1337;
        pPlayer->AkimboAmmoReserve = 1337;
        pPlayer->NumberOfGrenades = 1337;
        pPlayer->Akimbo = 1;

        logger.debug_log(_T("[+] Set ammo & grenades to 1337"));

        if (!originalAmmoDecrementBytes) {
            originalAmmoDecrementBytes = new BYTE[NOP_LENGTH]{};
        }

        if (mem.nop(ammoDecrementAddress, NOP_LENGTH, originalAmmoDecrementBytes)) {
            logger.debug_log(_T("[+] Set Infinite Ammo by NOPing decrement"));
        } else {
            logger.debug_log(_T("[-] Unable to set Infinite Ammo by NOPing decrement"));
            totalSuccess = false;
        }

        if (!originalGrenadeDecrementBytes) {
            originalGrenadeDecrementBytes = new BYTE[NOP_LENGTH]{};
        }

        if (mem.nop(grenadeDecrementAddress, NOP_LENGTH, originalGrenadeDecrementBytes)) {
            logger.debug_log(_T("[+] Set Infinite Grenades by NOPing decrement"));
            return totalSuccess;
        }

        logger.debug_log(_T("[-] Unable to set Infinite Grenades by NOPing decrement"));
        return false;
    }

    if (originalAmmoDecrementBytes) {
        totalSuccess = mem.writeMem(ammoDecrementAddress, originalAmmoDecrementBytes, NOP_LENGTH, nullptr);
    }

    if (originalGrenadeDecrementBytes) {
        totalSuccess = totalSuccess && mem.writeMem(grenadeDecrementAddress, originalGrenadeDecrementBytes, NOP_LENGTH, nullptr);
    }

    return totalSuccess;
}

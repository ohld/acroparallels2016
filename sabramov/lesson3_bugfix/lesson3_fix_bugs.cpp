/**
* @brief
*		Find errors and decrease probability of getting errors of the same kind in the future
*		This piece of code won't compile and it doesn't describe an entire algorithm: just part of some page storage
*
* @author
*		AnnaM
*/

#include <Windows.h>
#include <stdio.h>   // FIXED:  Added string.h, new, iostream   
#include <string.h> 
#include <new>
#include <iostream>

// FIXED: 
// Now enum begins from 0 (need for arrays and here is
// no reasons for begin it from 1) 
// Added PG_NUMBER_OF_COLOURS to avoid write magic constants
// in arrays declaration also we can easily expand number of page
// states 

enum PAGE_COLOR																						
{
    PG_COLOR_GREEN, /* page may be released without high overhead */         
	PG_COLOR_YELLOW, /* nice to have */									       
    PG_COLOR_RED,	/* page is actively used */							   
    PG_NUMBER_OF_COLORS 												    
};    																	   																	 



/**
 * UINT Key of a page in hash-table (prepared from color and address)
 */


union PageKey
{
	struct
	{
        UINT	cColor: 8;   			// FIXED: Changed CHAR on UINT                                              
		UINT	cAddr: sizeof(UINT) * 8 - 8;  // FIXED: Also fixed cAddr field												   
	};																	    
	UINT	uKey;														    
};								

// FIXED:
// Added round brackets due to operation's priority																		   
// Added type cast to UINT, it is necessary for PageFind and PageInit
/* Prepare from 2 chars the key of the same configuration as in PageKey */          
#define CALC_PAGE_KEY(Addr, Color)	((Color) + ((UINT)(Addr) << 8 )) 				     	         
																			
/**
 * Descriptor of a single guest physical page
 */
struct PageDesc
{
	PageKey			uKey;	

	/* list support */
	PageDesc		*next, *prev;
};

// FIXED: 
// Added "do while"      				
// Changed (Desc).uKey on (Desc).uKey.uKey to reach uKey in PageKey
#define PAGE_INIT(Desc, Addr, Color)                 \
    do {                                               \
        (Desc).uKey.uKey = CALC_PAGE_KEY(Addr, Color);    \
        (Desc).next = (Desc).prev = nullptr;              \
    } while(0)                                                             
        


/* storage for pages of all colors */
static PageDesc* PageStrg[PG_NUMBER_OF_COLORS];			// FIXED:
									// If "PG_NUMBER_OF_COLORS" is determined in enum
									// it should be used here for scalability
								  
																			

void PageStrgInit()																	
{
	memset(PageStrg, 0, sizeof(*PageStrg) * PG_NUMBER_OF_COLORS);  // FIXED:      		
}																   // To initialize array memset 
																   // needs size of arrays element 		
																			
#define FIND_LOOP(slow, fast) \
do { \
	 if (fast->next) \
	 	fast = fast->next->next; \
	 if ((fast == slow) && (fast->next != NULL)) \
	 	return nullptr; \
} while(0)



PageDesc* PageFind(void* ptr, UINT color)			  // FIXED: Change char on UINT 					  
{
    if (color >= PG_NUMBER_OF_COLORS || ptr == nullptr)  // FIXED: Check color to avoid + Check if ptr == NULL
    	return nullptr;	  					  				  		// exit array bounds 													 	
    
	PageDesc* pgFast = PageStrg[color];
    
    for (PageDesc* pgSlow = PageStrg[color]; pg; pgSlow = pgSlow->next)   // FIXED: Deleted 
 	{																      //semicolomn in "for"                  
		FIND_LOOP(pgSlow, pgFast);  // to avoid infinit loop    	
    	
    	if (pgSlow->uKey.uKey == CALC_PAGE_KEY(ptr, color)) 	  // FIXED: changed Pg->uKey to Pg->uKey.uKey	                    
    		return pgSlow;   									  				
    }    																	 
    
    return nullptr;											  
}

PageDesc* PageReclaim(UINT cnt)
{
	UINT color = 0;
    PageDesc* Pg = PageStrg[0];         // FIXED: Initialized Pg
	
	while (cnt)														   	    	
    {
        if (Pg == NULL)			    	// FIXED: Need check Pg at start                                                     
        {                                                                   
            color++;
            
            if (color == PG_NUMBER_OF_COLORS)	// FIXED: Added check if color > number of states 
            	break;
            
            Pg = PageStrg[color];
        	continue;
        }
		
			Pg = Pg->next;
			PageRemove(PageStrg[color]);
		cnt--;		
	}    
    
    return Pg;                                 // FIXED: Need to return Pg
}
            
PageDesc* PageInit(void* ptr, UINT color)
{
    if (color > PG_NUMBER_OF_COLORS || ptr == nullptr)  // FIXED: Check color to avoid + Check if ptr == NULL
    	return nullptr;
    	
    try
    {
        PageDesc* pg = new PageDesc;			// FIXED: "New" can throw exception bad_alloc
        
        if (pg)
            PAGE_INIT(*pg, ptr, color);         // FIXED: Changed & on *     
        else                                                               
            printf("Allocation has failed\n");
        
        return pg;
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what() << endl;
        return nullptr;
    }
}


/**
 * Print all mapped pages
 */
void PageDump()
{
	UINT color = 0;
	
	#define PG_COLOR_NAME(clr) #clr
	
	char* PgColorName[] = 
	{
        PG_COLOR_NAME(PG_COLOR_GREEN),             // FIXED: Fixed wrong order of colors                           
		PG_COLOR_NAME(PG_COLOR_YELLOW),		
        PG_COLOR_NAME(PG_COLOR_RED)
	};

		
	while( color < PG_NUMBER_OF_COLORS)		// FIXED: Change PG_COLOR_RED  on PG_NUMBER_OF_COLORS for scalability
	{
        printf("PgStrg[(%s) %u] ********** \n", PgColorName[color], color );    // FIXED: Wrong order of arguments
        
        for( PageDesc* pgSlow = PageDesc* pgFast = PageStrg[color++]; Pg != NULL; Pg = Pg->next)  // FIXED: Here should be postfix ++
		{
			FIND_LOOP(pgSlow, pgFast);         							// write fuction but I hope repeating		
            
            if ((Pg->uKey).cAddr == NULL)                               // of 2 lines won't be so bad     	
            	continue;														
            															
            															// FIXED: Change "=" on "==" 
                														// FIXED: Pg is pointer to PageDesc, so need  			
																		// (Pg->uKey).cAddr, there is no uAddr			
			
			printf("Pg :Key = 0x%x, addr %p\n", (Pg->uKey).uKey, (void*)(Pg->uKey).cAddr);// FIXED: The same as in previous 			
															// and %p: needed (void*)   	
		}
	}
	#undef PG_COLOR_NAME
}




